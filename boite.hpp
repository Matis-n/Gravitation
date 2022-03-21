//=================================================================================
//                        class Boite
//=================================================================================

#ifndef BOITE_HPP
#define BOITE_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include "particule.hpp"
#include "surcharge_vect.hpp"
using namespace std;

const int taille=100;
const double g = 9.8;
const double epsilon = 0.1 ; 
const double G=6.67*pow(10,-11);
const double dt=0.1;
const double distance_threshold = 0.1;


class Boite {
    public :
        //Attributs
        int level; //niveau
        double mass;       //masse
        vector<double> center; //centre de la boîte
        vector<double> center_mass; //centre de masse
        Particule* particule; // pointeur vers une particule
        Boite* fille; //pointeur vers la première boîte fille
        Boite* soeur;//pointeur vers la boîte soeur

        //Constructeurs
        Boite(vector<double> center,int level=0,double m=0.0); //constructeur à partir d'un centre et d'un niveau

        ~Boite(); //destructeur

        //Méthodes
        void diviser_boite();
        bool particule_in_boite(Particule& p);
        bool boite_in_boite(Boite B);
        void ajouter(Particule& p); //ajoute une particule dans la boite
        void supprimer_fille(); // supprime toutes les boites filles de la boîte
        void retirer(Particule& p,Boite B); // retire une particule de la boite
        vector<double> calcul_force(Particule P, double distance_threshold, double eps,vector<double> actual_force)  ; //calcul force gravitationelle exercée par la boîte sur la particule 

};



#endif