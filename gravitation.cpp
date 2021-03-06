#include <iostream>
#include <cmath>
#include <list>
#include <random>
#include <vector>
#include "gravitation.hpp"

const double pi=3.1415;

std::list<Particule>::iterator it;
void maj_forces(std::list<Particule>& liste_particules,double distance_threshold,double eps,Boite B){ 
    vector<double> f(2); //vecteur nul
    for (it=liste_particules.begin();it!=liste_particules.end();it++){
        printf("matis\n");
        it->force=B.calcul_force(*it,distance_threshold,eps,f);
    }
}

void maj_positions_vitesses(std::list<Particule>& liste_particules)
{
    for ( it=liste_particules.begin();it!=liste_particules.end();it++){ 
        ///printf("Antoine\n");
        it->vitesse=it->vitesse + dt*(1.0/it->masse)*(it->force);
        it->position=it->position+dt*(it->vitesse);
    }
}

void maj_boites(Boite& B,Boite& B0){
    if (B.soeur!=nullptr){
       //printf("if1\n");
        maj_boites(*B.soeur,B0);

    }
    if (B.fille!=nullptr){
       //printf("if2\n");
        maj_boites(*B.fille,B0);
    }
    else {
       //printf("else2\n");
        if(B.particule!=nullptr && B.particule->position.size()==2){
           //printf("hugo\n");
           //printf("%ld\n",B.particule->position.size());
           //printf("%f\n",B.particule->position.at(0));
            if (!(B.particule_in_boite(*B.particule))){
               //printf("if4\n");
                B0.retirer(*B.particule,B);
                B0.ajouter(*B.particule);
            }  
        }
        
    }
}

std::list<Particule> initialisation(int number_particules){
    std::list<Particule> liste_particules;
    std::srand(time(nullptr));
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
        liste_particules.push_back(Particule(1.0/number_particules,position,vitesse));
    }
    return liste_particules;
}


Boite init_boite(std::list<Particule> liste_particules){
    std::vector<double> V0(2);
    

    Boite B0(V0);
    ///printf("B0 : %ld\n",B0.center.size());
    for ( it=liste_particules.begin();it!=liste_particules.end();it++){ 
        ///printf("it_pass\n");
        B0.ajouter(*it);

    }
    return B0;
}