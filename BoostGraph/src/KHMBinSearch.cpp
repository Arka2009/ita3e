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
#include "DataTypes.hpp"
#include "ATG.hpp"

/* Minimum peak power scheduling */
void AppTaskGraph::KHMBinSearch(int K) {
  int mx = 1; // Controls the KHM scheduling internally, varies from 1 to M
  int ub = M;
  int lb = 1;
  int i = 0;

  while(i++ < K) {
      this->reset();
      mx = (lb+ub)/2;
      printf("-----------------------------------\n");
      printf("MX = %d\n",mx);
      printf("-----------------------------------\n");
      double C = this->KlausHuangMethodSched(mx);
      printf("-----------------------------------\n");
      printf("Iteration = %d, Makspan = %f, deadline = %f\n",i,C,this->deadline);
      printf("-----------------------------------\n");
      if (C > this->deadline) {
          lb = mx;
      } else {
          ub = mx;
      }
    //   this->writeDot(i);
  }
}