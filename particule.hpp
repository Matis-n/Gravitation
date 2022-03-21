#ifndef PARTICULE_HPP
#define PARTICULE_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

//=================================================================================
//                        class Particule
//=================================================================================

class Particule
{  public:
    //attributs
    double masse;
    vector<double> position;
    vector<double> vitesse;
    vector<double> force;

    //constructeur
    Particule(double m,vector<double> p,vector<double> v);
    
        
};

#endif