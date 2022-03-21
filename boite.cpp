#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include "boite.hpp"

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

//=================================================================================
//                        class Boite
//=================================================================================

//Constructeurs Boîte
Boite::Boite(vector<double> center,int level,double m){
            this->level=level; this->mass=m;this->center=center; this->center_mass=center; 
            vector<double> v(2);
            particule=nullptr;
            fille=nullptr;
            soeur=nullptr;
}

Boite::~Boite(){
    delete(particule);delete(fille);delete(soeur);
}



//création des sous-boîtes
void Boite::diviser_boite(){
    double d=taille/pow(2,level+1);

    vector<double> c1;
    c1.push_back(center.at(0)-d); c1.push_back(center.at(1)+d);
    Boite B1(c1,level+1);

    vector<double> c2;
    c2.push_back(center.at(0)+d); c2.push_back(center.at(1)+d);     
    Boite B2(c2,level+1);

    vector<double> c3;
    c3.push_back(center.at(0)+d); c3.push_back(center.at(1)-d);
    Boite B3(c3,level+1);

    vector<double> c4;
    c4.push_back(center.at(0)-d); c4.push_back(center.at(1)-d);
    Boite B4(c4,level+1);

    fille=&B1;
    B1.soeur=&B2;
    B2.soeur=&B3;
    B3.soeur=&B4;
}

bool Boite::particule_in_boite(Particule& p){
    return( (p.position.at(0)>center.at(0)-(taille/pow(2,level)))&&(p.position.at(0)<center.at(0)+(taille/pow(2,level)) ) && ( p.position.at(1)>center.at(1)-(taille/pow(2,level)) ) && (p.position.at(1)<center.at(1)+(taille/pow(2,level))) );
}

void Boite::ajouter(Particule& p){
    //condition si la position de la particule est bien dans la boîte 
    if(particule_in_boite(p)){

        //Particule terminale ou non ? 
        if (fille==nullptr){//boîte terminale
            if (mass==0){ //boîte vide 
                particule=&p; //particule est un pointeur 
                mass=p.masse;
                center_mass=p.position;
            }
            else if (mass>0){ //boîte non vide
                center_mass=p.masse*p.position+mass/(mass+p.masse)*center_mass;//calcul nouveau centre de masse
                mass+=p.masse; //nouvelle masse de la boîte de niveau plus faible
                //création de nouvelles sous-boîtes
                diviser_boite();
                ajouter(p);
                ajouter(*particule);// on n'oublie pas d'ajouter la particule déjà présente dans la boîte}
            }
        }
        else{
            fille->ajouter(p);
        }
    }  

    else {
        if (soeur!=nullptr){
            soeur->ajouter(p);
        }
    }

}

/*
void Boite::supprimer_fille(){
    if (fille!=nullptr){
        fille->supprimer_fille();
        fille=nullptr;
    }
}

void Boite::retirer(Particule& p){
    //condition si la position de la particule est bien dans la boîte 
    if(particule_in_boite(p)){
        if(mass==p.masse){// la particule est la seule dans la boite
            //on supprime toutes les sous boites
            mass=0;
            supprimer_fille();
        }
        else{
            //on met a jour les masses va voir les sous boites
            center_mass=1/(mass-p.masse)*(mass*center_mass+p.masse*p.position);//calcul nouveau centre de masse
            mass-=p.masse; //nouvelle masse de la boîte de niveau plus faible
            //on va voir dans sa fille
            fille->retirer(p);
        }
    }  

    else {
        if (soeur!=nullptr){
            soeur->retirer(p);
        }
    }
}


Vecteur& Boite::calcul_force(Particule P, double distance_threshold, double eps,Vecteur& actual_force){
    Vecteur& force(actual_force); //initialisation vecteur force gravitaionelle par copie de la force actuelle

    if (mass!=0){ //on vérifie qu'il y a une particule dans la boîte
        
        double r= sqrt((center_mass(1)-P.position(1))*(center_mass(1)-P.position(1))+(center_mass(2)-P.position(2))*(center_mass(2)-P.position(2)));//distance centre-masse boîte/particule
        double d=taille/pow(2,level+1); //

        if (r/d>=distance_threshold) { //si la boîte est éloignée => on fait le calcul approché 
            force=actual_force-G*mass*P.masse/((d*d)+(r*r)) ;
            if (soeur==nullptr) { return force;} 
            else{return soeur->calcul_force(P, distance_threshold, eps,force);} //sinon on ajoute la force exercée par la boîte soeur 
        }

        else{ //si la boîte est proche => calcul exact sur les boîtes terminales de cette boîte 

            if(fille!=nullptr){ //Si la boîte n'est pas terminale 
                return fille->calcul_force(P,distance_threshold,eps,actual_force)+soeur->calcul_force(P,distance_threshold,eps,actual_force);
            }


            else { //Si la boîte est terminale 
                if (soeur==nullptr){// critère d'arrêt si pas de boîte soeur
                    return actual_force - G*mass*P.masse/((d*d)+(r*r));} 


                else{ //la boîte possède une boîte soeur 
                    force=actual_force -G*mass*P.masse/((d*d)+(r*r));
                    return soeur->calcul_force(P, distance_threshold, eps,force);
                }
            }   
        }
    }
    else {
         return soeur->calcul_force(P,distance_threshold,eps,actual_force); //si pas de particule on passe à la soeur 
         } 
}
*/