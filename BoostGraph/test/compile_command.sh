#!/bin/bash

#g++ --std=c++11 -I/home/amaity/Desktop/ibm/ILOG/CPLEX_Studio_Community129/cplex/include -I/home/amaity/Desktop/ibm/ILOG/CPLEX_Studio_Community129/concert/include -DIL_STD plantlocation.cpp -o test2 -lilocplex -lconcert -lcplex -lm -lpthread -ldl

g++ --std=c++11 -I$GUROBI_HOME/include -I$PWD -L$GUROBI_HOME/lib TestKlausHuangLP.cpp KlausHuangLP.cpp -o test2 -lgurobi_c++ -lgurobi81
