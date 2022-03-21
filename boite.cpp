#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include "boite.hpp"




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

/*Boite::~Boite(){
    printf("delete0\n");
    if (fille!=nullptr){
        printf("delete1\n");
        delete [] fille;
    }
    if (soeur!=nullptr){
        printf("delete2\n");
        delete(soeur);
    }

}*/
Boite::~Boite(){}



//création des sous-boîtes
void Boite::diviser_boite(){
    //printf("divis_boite_pass\n");
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
    printf("creation_pass\n");
}

bool Boite::particule_in_boite(Particule& p){
    return( (p.position.at(0)>center.at(0)-(taille/pow(2,level)))&&(p.position.at(0)<center.at(0)+(taille/pow(2,level)) ) && ( p.position.at(1)>center.at(1)-(taille/pow(2,level)) ) && (p.position.at(1)<center.at(1)+(taille/pow(2,level))) );
}

bool Boite::boite_in_boite(Boite B){
    return( (B.center.at(0)>center.at(0)-(taille/pow(2,level)))&&(B.center.at(0)<center.at(0)+(taille/pow(2,level)) ) && ( B.center.at(1)>center.at(1)-(taille/pow(2,level)) ) && (B.center.at(1)<center.at(1)+(taille/pow(2,level))) );

}




void Boite::supprimer_fille(){
    if (fille!=nullptr){
        fille->supprimer_fille();
        free(fille);
    }
}

void Boite::retirer(Particule& p,Boite B){
    //condition si la position de la particule est bien dans la boîte 
    if(boite_in_boite(B)){
        printf("bib_pass\n");
        if(mass==p.masse){// la particule est la seule dans la boite
            particule=nullptr; //on supprime toutes les sous boites
            mass=0;
            supprimer_fille();
            printf("supfille_pass\n");
        }
        else{
            //on met a jour les masses va voir les sous boites
            
            center_mass=(1/(mass-p.masse))*(mass*center_mass+p.masse*p.position);//calcul nouveau centre de masse
            mass-=p.masse; //nouvelle masse de la boîte de niveau plus faible
            //on va voir dans sa fille
            printf("maj_pass\n");
            fille->retirer(p,B);
            printf("retirer_fin_pass\n");
        }
    }  

    else {
        printf("else_pass\n");
        if (soeur!=nullptr){
            soeur->retirer(p,B);
        }
    }
}

void Boite::ajouter(Particule& p){
    //condition si la position de la particule est bien dans la boîte 
    if(particule_in_boite(p)){

        //Particule terminale ou non ? 
        if (fille==nullptr){//boîte terminale
            printf("ajout_pass\n");
            if (mass==0){ //boîte vide 
                particule=&p; //particule est un pointeur 
                mass=p.masse;
                center_mass=p.position;
                printf("m0_pass\n");
            }
            else { //boîte non vide
                printf("mpas0_pass\n");
                center_mass=p.masse*p.position+mass/(mass+p.masse)*center_mass;//calcul nouveau centre de masse
                mass+=p.masse; //nouvelle masse de la boîte de niveau plus faible
                //création de nouvelles sous-boîtes
                diviser_boite();
                printf("divis_pass\n");
                retirer(*particule,*this);
                printf("retirer_pass\n");
                fille->ajouter(p);
                fille->ajouter(*particule);// on n'oublie pas d'ajouter la particule déjà présente dans la boîte}
            }
        }
        else{
            center_mass=p.masse*p.position+mass/(mass+p.masse)*center_mass;//calcul nouveau centre de masse
            mass+=p.masse; //nouvelle masse de la boîte de niveau plus faible
            fille->ajouter(p);
        }
    }  

    else {
        if (soeur!=nullptr){
            soeur->ajouter(p);
        }
    }

}

vector<double> Boite::calcul_force(Particule P, double distance_threshold, double eps,vector<double> actual_force)  {
    vector<double> force=actual_force; //initialisation vecteur force gravitationelle par copie de la force actuelle

    if (mass!=0){ //on vérifie qu'il y a une particule dans la boîte
        
        double r= sqrt((center_mass.at(0)-P.position.at(0))*(center_mass.at(0)-P.position.at(0))+(center_mass.at(1)-P.position.at(1))*(center_mass.at(1)-P.position.at(1)));//distance centre-masse boîte/particule
        double d=taille/pow(2,level+1); //

        if (r/d>=distance_threshold) { //si la boîte est éloignée => on fait le calcul approché 
            //force=actual_force+(-G)*mass*P.masse/((d*d)+(r*r)) ; // /!\ ON AJOUTE UN VECTEUR ET UN SCALAIRE, IL FAUT PROJETER LA FORCE EN FAIT COMME EN DESSOUS
            force.at(0)=(center.at(0)-P.position.at(0)/r)*(-G)*mass*P.masse/((d*d)+(r*r))+actual_force.at(0);
            force.at(1)=(center.at(1)-P.position.at(1)/r)*(-G)*mass*P.masse/((d*d)+(r*r))+actual_force.at(1);
            if (soeur==nullptr) { return force;} 
            else{return soeur->calcul_force(P, distance_threshold, eps,force);} //sinon on ajoute la force exercée par la boîte soeur 
        }

        else{ //si la boîte est proche => calcul exact sur les boîtes terminales de cette boîte 

            if(fille!=nullptr){ //Si la boîte n'est pas terminale 
                return fille->calcul_force(P,distance_threshold,eps,actual_force)+soeur->calcul_force(P,distance_threshold,eps,actual_force);
            }


            else { //Si la boîte est terminale 
                if (soeur==nullptr){// critère d'arrêt si pas de boîte soeur
                    force.at(0)=actual_force.at(0)+(center.at(0)-P.position.at(0)/r)*(-G)*mass*P.masse/((d*d)+(r*r));
                    force.at(1)=actual_force.at(1)+(center.at(1)-P.position.at(1)/r)*(-G)*mass*P.masse/((d*d)+(r*r));
                    return force;} 


                else{ //la boîte possède une boîte soeur 
                    force.at(0)=actual_force.at(0)+(center.at(0)-P.position.at(0)/r)*(-G)*mass*P.masse/((d*d)+(r*r));
                    force.at(1)=actual_force.at(1)+(center.at(1)-P.position.at(1)/r)*(-G)*mass*P.masse/((d*d)+(r*r));
                    //force=actual_force -G*mass*P.masse/((d*d)+(r*r));
                    return soeur->calcul_force(P, distance_threshold, eps,force);
                }
            }   
        }
    }
    else {
         return soeur->calcul_force(P,distance_threshold,eps,actual_force); //si pas de particule on passe à la soeur 
         } 
}
