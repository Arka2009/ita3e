#include <ilcplex/ilocplex.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int num_of_threads = 1;

int main () {
	
	IloEnv env;
	stringstream logfile;

	try {
		IloModel model(env);
		IloNumVarArray vars(env);
		IloRangeArray con(env);
		IloCplex cplex(model);

		// Set options of IP solver
		cplex.setParam(IloCplex::TiLim, 100.000);
		cplex.setParam(IloCplex::Threads, num_of_threads);
		cplex.setParam(IloCplex::EpGap, 0.0);
		cplex.setParam(IloCplex::EpAGap, 0.0);
		cplex.setOut(logfile);

		// Variables
		vars.add(IloNumVar(env, 0.0, 40.0));
		vars.add(IloNumVar(env));
		vars.add(IloNumVar(env));
		model.add(IloMaximize(env, vars[0] + 2 * vars[1] + 3 * vars[2]));
		model.add( - vars[0] +     vars[1] + vars[2] <= 20);
		model.add(   vars[0] - 3 * vars[1] + vars[2] <= 30);

		// Solve
		cplex.solve();
		if (cplex.getStatus() == IloAlgorithm::Optimal) {
			IloNumArray vals(env);
			cplex.getValues(vals, vars);
			env.out() << "Values = " << vals << endl;
		}
	} catch (IloException& e) {
		cerr << "C-Exp: " << e << endl;
	} catch (...) {
		cerr << "Unknown Exception" << endl;
	}

	const string str = logfile.str();
	cout << str << endl;
	env.end();

	return 0;
}