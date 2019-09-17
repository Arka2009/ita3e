#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <typeinfo>

int main() {
    for (int m = 1; m <= 32; m++) {
        int mu = (113*m - std::sqrt(6469*m*m - 6300*m))/100;
        int mu2 = (m+1)/2;
        std::cout<<"m:"<<m<<",mu:"<<mu<<",mu2:"<<mu2<<std::endl; 
    }
    return 0;
}
