#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <random>
#include "boite.hpp"


using namespace std;

//nicolas kielbasievicz
//nicolas.kielbasievicz@ensta-paris.fr

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

void maj_forces(std::list<Particule> liste_particules,double distance_threshold,double eps);
void maj_positions_vitesses(std::list<Particule> liste_particules);

#endif
