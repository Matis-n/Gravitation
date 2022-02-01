#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int taille=100;

//=================================================================================
//                        class Point (salut c'est hugo hihi)
//=================================================================================
class Point
{ public:
    double x,y;  //2D Point coordinates
    Point(double xi=0., double yi=0.)  : x(xi),y(yi){}
	Point& operator+=(const Point& p);
    Point& operator-=(const Point& p);
    Point& operator*=(double a);
};
Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);
Point operator*(double a, const Point& p);
double operator*(const Point& p1, const Point& p2); // produit vectoriel 2D
double operator|(const Point& p1, const Point& p2); // produit scalaire  2D
double norme(const Point& p);                       // norme euclidienne
ostream& operator<<(ostream& out, const Point& p);

//=================================================================================
//                        class Particule
//=================================================================================

class Particule
{ public:
    //attributs
    Point position;
    double masse;

    //constructeur
    Particule(Point p,double m);
};

//=================================================================================
//                        class Boite
//=================================================================================


class Boite {
    public :
        int level; //niveau
        Point center; //centre de la boîte
        Point center_mass; //centre de masse
        double mass;       //masse
        Particule& particule; //référence vers une particule
        Boite* fille; //pointeur vers la première boîte fille
        Boite* soeur;//pointeur vers la boîte soeur

        //constructeur d'une boîte vide terminale
        Boite(Point c,int l,double m=0) : level(l), center(c), center_mass(c),mass(m) {
            fille=nullptr;
            soeur=nullptr;
            particule=Particule(c,0.); 
        } 
        ~Boite(); //destructeur
        void ajouter(Particule& p); //ajoute une particule dans la boite
        void retirer(Particule& p); // retire une particule de la boite
        void diviser_boite();
        bool particule_in_boite(Particule& p);
};

//création des sous-boîtes
void Boite::diviser_boite(){
    double d=taille/pow(2,level+1);

    Point c1(center-d,center+d);
    Boite B1(c1,level+1);

    Point c2(center+d,center+d);
    Boite B2(c2,level+1);

    Point c3(center+d,center-d);
    Boite B3(c3,level+1);

    Point c4(center-d,center-d);
    Boite B4(c4,level+1);

    Boite.fille=&B1;
    B1.soeur=&B2;
    B2.soeur=&B3;
    B3.soeur=&B4;
}

bool Boite::particule_in_boite(Particule& p){
    return( (p.position.x>center.x-(taille/pow(2,level)))and  (p.position.x<center.x+(taille/pow(2,level)) ) and ( p.position.y>center.y-(taille/pow(2,level)) ) and (p.position.y<center.y+(taille/pow(2,level))) );
}

void Boite::ajouter(Particule& p){
    //condition si la position de la particule est bien dans la boîte 
    if(particule_in_boite){

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
        else{
            fille->ajouter(p);}
    }  

    else {
        if (soeur!=nullptr){
            soeur->ajouter(p);
        }
    }

}




#endif
