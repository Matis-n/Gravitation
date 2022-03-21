#include <iostream>
#include <cmath>
#include "gravitation.hpp"
#include <list>
#include <random>
#include <vector>


/*
const double g = 9.8;
const double epsilon = 0.1 ; 
const double G=6.67*pow(10,-11);
const double dt=0.1;*/


std::list<Particule>::iterator it;
void maj_forces(std::list<Particule> liste_particules,double distance_threshold,double eps,Boite B){ 
    vector<double> f(2); //vecteur nul
    for (it=liste_particules.begin();it!=liste_particules.end();it++){
        it->force=B.calcul_force(*it,distance_threshold,eps,f);
    }
}

void maj_positions_vitesses(std::list<Particule> liste_particules)
{
    for ( it=liste_particules.begin();it!=liste_particules.end();it++){ 
        it->vitesse=it->vitesse + (it->force/it->masse)*dt;
        it->position=it->position+it->vitesse*dt;
    }
}
/*
std::list<Particule> initialisation(int number_particules){
    std::list<Particule> liste_particules;
    std::srand(std::time(nullptr));
    double x,y,z,X1,X2,X3,X4,X5,X6,X7,q,V,u,v,w;
    X1=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
    double r=pow((pow(X1,-2/3)-1),-1/2);
    double Ve=sqrt(2)*pow((1+r*r),-1/4);

    for (int i=0;i<number_particules;i++){
        X2=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        X3=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        z=(1-2*X2)*r;
        x=sqrt(r*r-z*z)*cos(2*pi*X3);
        y=(r*r-z*z)*sin(2*pi*X3);
        X4=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        X5=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        if (X5<10*X4*X4*pow((1-X4*X4),7/2)){
            q=X4;
        }
        else {
            X4=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));X5=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        }
        V=q*Ve;
        X6=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));X7=FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        w=(1-2*X6)*V;v=sqrt(V*V-w*w)*cos(2*pi*X7);u=sqrt(V*V-w*w)*sin(2*pi*X7);
         
        vector<double> vitesse;
        vector<double> position;
        vitesse.push_back(u);vitesse.push_back(v);vitesse.push_back(w);
        position.push_back(x);position.push_back(y);
        position.push_back(z);
        liste_particules.push_back(Particule(1,position,vitesse));
    }
}
*/