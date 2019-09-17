#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <gurobi_c++.h>
#include "DataTypes.hpp"
#include "ATG.hpp"

/* Execute a tick */
int AppTaskGraph::execute(int M_X, double delta) {
    // int this->util = 0;
    for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
        NodeType *nd = &(this->gSS[*it]);
        if (nd->status == Active) {
            /* Execution finished */
            if (this->t >= nd->C + nd->start_time) {
                nd->status = Finished;
                nd->stop_time = this->t;
                this->finishCounter++;
                // std::cout<<this->t<<" : Util : "<<this->util<<", Node made Finished : "<<*nd<<std::endl;
                this->util -= nd->alloc;
            }
        }
        else if (nd->status == NotReady) {
            /* All the predecessors have finished */
            auto preds = this->getPreds(*it);
            bool fin   = true;
            for (auto jt = preds.begin(); jt != preds.end(); jt++) {
                NodeType *ndPred = &(this->gSS[*jt]);
                if (ndPred->status == Finished) {
                  fin &= true;
                } else {
                  fin &= false;
                }
            }
            if (fin) {
              nd->status = Ready;
              // std::cout<<this->t<<" : Node made Ready : "<<*nd<<std::endl;
            }
        }
    }

    for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
      NodeType *nd = &(this->gSS[*it]);
      if (nd->status == Ready) {
          if (this->util + nd->alloc <= M_X) {
              nd->start_time = this->t;
              nd->status = Active;
              // std::cout<<this->t<<" : Util : "<<this->util<<", Node made Active : "<<*nd<<std::endl;
              this->util += nd->alloc;
          } else {
            // std::cout << this->t<<" : Node could not be started, no resources available\n";
          }
        } else {
          // std::cout<<this->t<<" : Blah Node : "<<*nd<<",finishCounter:"<<this->finishCounter<<std::endl;
      }
    }
    this->t += delta;
    return this->util;
}


double AppTaskGraph::KlausHuangListM(int M_X, double delta) {
  /* Applying Graham's list scheduling */
  int N    = this->vdMap.size();

  /* Schedule all the independent nodes */
  this->t    = 0.0;
  this->util = 0;
  for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
    NodeType *nd = &(this->gSS[*it]);
    if (nd->estart == 0) {
        if (this->util + nd->alloc <= M_X) {
            nd->status = Active;
            this->util += nd->alloc;
            nd->start_time = 0.0;
            // std::cout<<"Node-"<<nd->id<<" to start initial execution \n";
        } else {
            nd->status = Ready;
            // std::cout<<"Node-"<<nd->id<<" made ready \n";
        }
    }
  }


  this->finishCounter = 0;
  while(this->finishCounter < N) {
    this->execute(M_X,delta);
    // std::cout << this->t << " : Utilization = "<<this->util<<std::endl;    
  }
  #ifdef DEBUG
//   std::cout<<"ATG (normalized) total work : "<<W/M_X<<"\n";
  std::cout<<"ATG makespan : "<<this->t-1<<"\n";
  #endif
  return this->t-1;
}

double AppTaskGraph::KlausHuangMethodSched(int M_X) {
  double rho   = 0.26;
  double delta = 1.0;
  // int mu = std::floor((M+1)/2);
  int mu = M_X;
  this->KlausHuangLP(M_X,rho,mu);
  double mkp = this->KlausHuangListM(M_X,delta);
  // this->writeDot();
  std::cout<<"Maximum makespan = "<<this->wC<<std::endl;
  std::cout<<"Actual makespan = "<<mkp<<std::endl;
  std::cout<<"Deadline = "<<this->deadline<<std::endl;
  this->scheduled = true;
  return mkp;
}