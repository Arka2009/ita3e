#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <gurobi_c++.h>
#include "DataTypes.hpp"
#include "ATG.hpp"

/* 
 * with rho as the rounding strategy */
int AppTaskGraph::KlausHuangLP(int M_X, double rho, int mu) {
  int N = this->getSize();
  
  std::cout << "MT-Allotment phase started, solving Klaus-Huang LP formulation" << std::endl;

  try {
    GRBEnv env = GRBEnv();

    GRBModel model = GRBModel(env);

    // Create variable - x_{j,l}
    GRBVar x[NMax][M];
    for (int j = 0; j < N; j++) {
      for(int l = 0; l < M_X; l++) {
        x[j][l] = model.addVar(0.0,1.0,0.0,GRB_CONTINUOUS,"x");
      }
    }

    // Create variable - task finish time variables (C_j)
    GRBVar C_j[NMax], C;
    for (int j = 0; j < N; j++) {
      C_j[j] = model.addVar(0.0,GRB_INFINITY,0.0,GRB_CONTINUOUS,"C_j");
    }
    C = model.addVar(0.0,GRB_INFINITY,0.0,GRB_CONTINUOUS,"C");

    // Create contraints - Precedence 
    for (int j = 0; j < N; j++) {
      std::vector<DAGVertexType> preds = this->getPreds(j);
      for (std::vector<DAGVertexType>::iterator it = preds.begin(); it != preds.end(); it++) {
        GRBLinExpr constr_pred_Cij = 0;
        NodeType prevNode = this->getNode(*it);
        int i = prevNode.id;
        constr_pred_Cij += C_j[i] - C_j[j];
        for (int l = 0; l < M_X; l++) {
          double coeff = this->tau_j(j,l+1);
          constr_pred_Cij += coeff*x[j][l];
        }
        model.addConstr(constr_pred_Cij,GRB_LESS_EQUAL,0,"predConstrs");
      }
    }
    
    // Create contraints - Makespan
    for (int j = 0; j < N; j++) {
      model.addConstr(C_j[j]-C,GRB_LESS_EQUAL,0,"mkspanConstrs" );
    }

    // Create constraints - Resource
    GRBLinExpr constr_resc = 0;
    for (int j = 0; j < N; j++) {
        for (int l = 0; l < M_X; l++) {
          double coeff = (l+1) * this->tau_j(j,l+1);
          constr_resc += coeff * x[j][l];
        }
    }
    constr_resc += -M_X*C;
    model.addConstr(constr_resc,GRB_LESS_EQUAL,0,"recConstrs");

    // Unitary Constraints
    for (int j = 0; j < N; j++) {
      GRBLinExpr sum_resc = 0;
      for (int l = 0; l < M_X; l++) {
        sum_resc += x[j][l];
      }
      model.addConstr(sum_resc,GRB_EQUAL,1,"Unitary");
    }

    // Objective
    model.setObjective(1*C, GRB_MINIMIZE);

    // Optimize model
    model.optimize();

    /* Display */
    for (int j = 0; j < N; j++) {
      double x_opt       = 0.0;
      double tau_x_opt   = 0.0;
      int x_optD         = 0;    // Rounded down version
      int lb = 0, ub = 0;

      for (int l = 0; l < M_X; l++) {
        double eta       = x[j][l].get(GRB_DoubleAttr_X);
        double x_jl      = (l+1)*eta;
        tau_x_opt += this->tau_j(j,l+1)*(eta);
        x_opt     += x_jl;

        /* find the boundaries  for rounding down */
        if (eta > 0 && eta < 1) {
          lb = l+1;
          ub = lb+1;
        } else if (eta == 1) {
          lb = l+1;
          ub = lb;
        }
      }
      
      /* Round Down x */
      double pjlc = rho * this->tau_j(j,lb) + (1-rho) * this->tau_j(j,ub);
      if (tau_x_opt >= pjlc)
        x_optD = lb;
      else
        x_optD = ub;

      // std::cout<<"x_optD("<<j<<"):"<<x_optD<<"\n";
	    // std::cout<<"C_("<<j<<"):"<<C_j[j].get(GRB_DoubleAttr_X)<<"\n\n";
      
      NodeType *nd = &(this->gSS[this->vdMap[j]]);
      nd->alloc = std::min(mu,x_optD);
      nd->C     = this->tau_j(nd->id,nd->alloc);
    }
    
    this->computeHeight(false);
    
  } catch(GRBException e) {
    std::cout << "Error code = " << e.getErrorCode() << std::endl;
    std::cout << e.getMessage() << std::endl;
  } catch(...) {
    std::cout << "Exception during optimization" << std::endl;
  }

  return 0;
}