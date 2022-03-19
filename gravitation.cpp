#include <iostream>
#include <cmath>
#include "gravitation.hpp"
#include "Vecteur.hpp"
#include <list>


const int taille=100;
const double g = 9.8;
const double epsilon = 0.1 ; 
const double G=6.67*pow(10,-11);
const double dt=0.1;

//=================================================================================
//                            class Point
//=================================================================================
Point& Point::operator+=(const Point& p)
{ x+=p.x;y+=p.y;return *this;}
Point& Point::operator-=(const Point& p)
{ x-=p.x;y-=p.y;return *this;}
Point& Point::operator*=(double a)
{ x*=a;y*=a;return *this;}
Point operator+(const Point& p1, const Point& p2)
{ Point p=p1; return p+=p2;}
Point operator-(const Point& p1, const Point& p2)
{ Point p=p1; return p-=p2;}
Point operator*(double a, const Point& p)
{Point q=p; return q*=a;}
double operator*(const Point& p1, const Point& p2)  // 2D cross product
{ return (p1.x*p2.y-p2.x*p1.y);}
double operator|(const Point& p1, const Point& p2)
{ return (p1.x*p2.x+p1.y*p2.y);}
double norme(const Point& p)
{ return sqrt(p|p);}

ostream& operator<<(ostream& out, const Point& p)
{ out<<"("<<p.x<<","<<p.y<<")"; return out;}

//=================================================================================
//                        class Boite
//=================================================================================

Boite::Boite(Point c,int l,double m) : particule(c,0){
    level=l; center=c; center_mass=c;mass=m; 
    fille=nullptr;
    soeur=nullptr;
        }

//création des sous-boîtes
void Boite::diviser_boite(){
    double d=taille/pow(2,level+1);

    Point c1(center.x-d,center.y+d);
    Boite B1(c1,level+1);

    Point c2(center.x+d,center.y+d);
    Boite B2(c2,level+1);

    Point c3(center.x+d,center.y-d);
    Boite B3(c3,level+1);

    Point c4(center.x-d,center.y-d);
    Boite B4(c4,level+1);

    fille=&B1;
    B1.soeur=&B2;
    B2.soeur=&B3;
    B3.soeur=&B4;
}

bool Boite::particule_in_boite(Particule& p){
    return( (p.position.x>center.x-(taille/pow(2,level)))and  (p.position.x<center.x+(taille/pow(2,level)) ) and ( p.position.y>center.y-(taille/pow(2,level)) ) and (p.position.y<center.y+(taille/pow(2,level))) );
}

void Boite::ajouter(Particule& p){
    //condition si la position de la particule est bien dans la boîte 
    if(particule_in_boite(p)){

        //Particule terminale ou non ? 
        if (fille==nullptr){//boîte terminale
            if (mass==0){ //boîte vide 
                particule=p;
                mass=p.masse;
                center_mass=p.position;
            }
            else if (mass>0){ //boîte non vide
                center_mass=p.position*p.masse+center_mass*mass/(mass+p.masse);//calcul nouveau centre de masse
                mass+=p.masse; //nouvelle masse de la boîte de niveau plus faible
                //création de nouvelles sous-boîtes
                diviser_boite();
                ajouter(p);
                ajouter(particule);// on n'oublie pas d'ajouter la particule déjà présente dans la boîte}
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


Vecteur Boite::calcul_force(Particule P, double distance_threshold, double eps,Vecteur actual_force){
    Vecteur force(actual_force); //initialisation vecteur force gravitaionelle par copie de la force actuelle

    if (mass!=0){ //on vérifie qu'il y a une particule dans la boîte
        
        double r= sqrt((center_mass.x-P.position.x)*(center_mass.x-P.position.x)+(center_mass.y-P.position.y)*(center_mass.y-P.position.y));//distance centre-masse boîte/particule
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

std::list<Particule>::const_iterator it;
void maj_forces(std::list<Particule> liste_particules,double distance_threshold,double eps)
{
    for ( it=liste_particules.begin();it!=liste_particules.end();it++){
        it->force=calcul_force(*it,distance_threshold,eps);
    }
}

void maj_positions_vitesses(std::list<Particule> liste_particules)
{
    for ( it=liste_particules.begin();it!=liste_particules.end();it++){ 
        it->vitesse=it->vitesse + (it->force/it->masse)*dt;
        it->position=it->position+it->vitesse*dt;
    }
}

std::list<Particule> initialisation(int number_particules){
    std::list<Particule> liste_particules;
    double x,y,z,X1,X2,X3,X4,X5,X6,X7,q,V,u,v,w;
    X1=;
    double r=pow((pow(X1,-2/3)-1),-1/2);
    double Ve=sqrt(2)*pow((1+r*r),-1/4);

    for (int i=0;i<number_particules;i++){
        X2=
        X3=
        z=(1-2*X2)*r;
        x=sqrt(r*r-z*z)*cos(2*pi*X3);
        y=(r*r-z*z)*sin(2*pi*X3);
        X4=
        X5=
        if (X5<10*X4*X4*pow((1-X4*X4),7/2)){
            q=X4;
        }
        else {
            X4=;X5=;
        }
        V=q*Ve;
        X6=;X7=;
        w=(1-2*X6)*V;v=sqrt(V*V-w*w)*cos(2*pi*X7);u=sqrt(V*V-w*w)*sin(2*pi*X7);
        Vecteur e1(3,1);
        Vecteur e2(3,2);
        Vecteur e3(3,3); 
        Vecteur vitesse(3);
        Vecteur position(3);
        vitesse=e1*u+e2*v+e3*w;
        position=e1*x+e2*y+e3*z;
        liste_particules.push_back(Particule() )
    }
}
