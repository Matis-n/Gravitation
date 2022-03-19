#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include "Vecteur.hpp"
#include <list>
using namespace std;
#include "Vecteur.hpp"
//nicolas kielbasievicz
//nicolas.kielbasievicz@ensta-paris.fr
extern const int taille;

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
    Vecteur position;
    double masse;
    Vecteur vitesse;
    Vecteur force;

    //constructeur
    Particule(Vecteur p,double m,Vecteur v):position(p), masse(m),vitesse(v){
        force=Vecteur(2,0.0);
    };
    
};

Vecteur calcul_force(Particule P1, Particule P2);

//=================================================================================
//                        class Boite
//=================================================================================


class Boite {
    public :
        int level; //niveau
        Point center; //centre de la boîte
        Point center_mass; //centre de masse
        double mass;       //masse
        Particule particule; // particule
        Boite* fille; //pointeur vers la première boîte fille
        Boite* soeur;//pointeur vers la boîte soeur

        Boite(Point c); 
        //constructeur d'une boîte vide terminale

        Boite(Point c,int l,double m=0);

        //~Boite(); //destructeur
        void ajouter(Particule& p); //ajoute une particule dans la boite
        void retirer(Particule& p); // retire une particule de la boite
        void diviser_boite();
        void supprimer_fille(); // supprime toutes les boites filles de la boîte
        bool particule_in_boite(Particule& p);
        Vecteur calcul_force(Particule P, double distance_threshold, double eps,Vecteur actual_force); //calcul force gravitationelle exercée par la boîte sur la particule 

};


void maj_forces(std::list<Particule> liste_particules,double distance_threshold,double eps);
void maj_positions_vitesses(std::list<Particule> liste_particules);

#endif
