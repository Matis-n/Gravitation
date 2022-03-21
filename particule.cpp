#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include "particule.hpp"

using namespace std;

Particule::Particule(double m,vector<double> p,vector<double> v){
    this->masse=m;this->position=p;this->vitesse=v;
    vector<double> f(2);
    this->force=f;
    };