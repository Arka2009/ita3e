#include <iostream>
#include <cstdlib>
#include <exception>
#include "DataTypes.hpp"
#include "ATG.hpp"

void testATG(int N, double p) {
    AppTaskGraph atg(N,p);
    atg.writeDot(N);
}

int main(int argc, char **argv) {
	if (argc < 3) {
		throw std::invalid_argument("Enter total number of Nodes, and edge connection probability");
	}
	int    N = atoi(argv[1]);
	double p = atof(argv[2]);
    testATG(N,p);
    return 0;
}
