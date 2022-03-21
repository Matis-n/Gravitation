
#include <iostream>
#include <cmath>
#include <vector>
#include <list>


std::vector<double> operator*(const double a,std::vector<double> B){
    for (std::size_t i =0;i<B.size();++i){
        B[i]=a*B[i];
    }
    return B;
}
std::vector<double> operator+(std::vector<double> A,std::vector<double> B){
    for (std::size_t i =0;i<B.size();++i){
        B[i]=A[i]+B[i];
    }
    return B;
}

