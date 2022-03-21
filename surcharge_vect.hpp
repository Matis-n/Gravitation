#ifndef SURCHARGE_VECT_HPP
#define SURCHARGE_VECT_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <list>

std::vector<double> operator*(const double a,std::vector<double> B);

std::vector<double> operator+(std::vector<double> A,std::vector<double> B);


#endif