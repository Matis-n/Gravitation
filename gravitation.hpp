#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
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
    Point position;
    double masse;

    //constructeur
    Particule(Point p,double m):position(p), masse(m){
    };
    Vecteur calcul_force(Particule P);
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
        Particule particule; // particule
        Boite* fille; //pointeur vers la première boîte fille
        Boite* soeur;//pointeur vers la boîte soeur

        Boite(); 
        //constructeur d'une boîte vide terminale

        Boite(Point c,int l,double m=0);

        //~Boite(); //destructeur
        void ajouter(Particule& p); //ajoute une particule dans la boite
        void retirer(Particule& p); // retire une particule de la boite
        void diviser_boite();
        void supprimer_fille(); // supprime toutes les boites filles de la boîte
        bool particule_in_boite(Particule& p);

};

 
#endif
