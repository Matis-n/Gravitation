#include <iostream>
#include <cmath>
#include "gravitation.hpp"
#include "Vecteur.hpp"
#include <list>


const int taille=100;
const double G=6.67*pow(10,-11);

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
Boite::Boite(): particule(c,0){
    level=0;
    center_mass=;
    center=;
    mass=0.;
    fille=nullptr;
    soeur=nullptr;
}

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


 Vecteur Boite::calcul_force(Particule P, double critere, double eps){
     //boîte vide ? 
     if (mass==0){exit (-1);}
     else {
         Vecteur force(2,0.0);
         double r= sqrt((center_mass.x-P.position.x)*(center_mass.x-P.position.x)+(center_mass.y-P.position.y)*(center_mass.y-P.position.y));//distance centre masse particule
         double d=taille/pow(2,level+1);
         Vecteur direction(2,0.0);
         direction.val[0]=(center_mass.x-P.position.x)/r;
        direction.val[1]=(center_mass.y-P.position.y)/r;

         if (r/d>critere) { //boîte lointaine 
            force=-((P.masse*mass*G)/(r*r+eps*eps))*direction;
            return force;
         }
         else{
             P.calcul_force(particule);
         }
          
     }
}

 Vecteur Particule::calcul_force(Particule P){
    double distance=abs(P.position-position);
   Point direction=(P.position-position)/distance;
   Vecteur force(2,0.0);

}


