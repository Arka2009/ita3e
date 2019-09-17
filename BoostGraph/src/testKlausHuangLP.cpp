// #include "KlausHuangLP.hpp"
#include "DataTypes.hpp"
#include "ATG.hpp"

int main(int argc, char *argv[]) {
  int N = 6;        // Size of the ATG
  double p = 0.54;  // ATG generator parameter
  
  int M_X = 7;
  AppTaskGraph atg(N,p);
// atg.KlausHuangMethodSched(M_X);
  atg.KHMBinSearch(4);
  atg.genStats();
}