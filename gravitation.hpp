#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


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

}

//=================================================================================
//                        class Boite
//=================================================================================
class Boite {
    public :
        int level; //niveau
        Point center; //centre de la boîte
        Point center_mass; //centre de masse
        double mass;       //masse
        Particule& particule; //pointeur vers une particule
        Boite& fille; //pointeur vers la première boîte fille
        Boite& soeur;//pointeur vers la boîte soeur
        Boite(Particule& p, Point P(), int l=0) : level(l), center(P){
            particule=p;
            fille=NULL;
            soeur=NULL;
            mass=p.masse();
            center_mass=p.position();
        } //constructeur de la boîte racine de niveau 0
<<<<<<< HEAD
        void ajouter(Particule p); //ajoute une particule dans la boite
        void retirer(Particule p); // retire une particule de la boite
        vector f_interact(); // calcule la force d'interaction totale avec les autres particules
=======
        void ajouter(Particule& p); //ajoute une particule dans la boite
        void retirer(Particule& p); // retire une particule de la boite
        Vector f_interact(); // calcule la force d'interaction totale avec les autres particules
>>>>>>> c52a465dc69e254d962f81d8ccf0a6e05c5dbe66

};


void Boite::ajouter(Particule& p){
    //Particule terminale ou non ? 
    if (fille==NULL){//boîte terminale
        if (mass==0){ //boîte vide 
            particule=p;
            mass=p.masse();
            center_mass=p.position();


        }
    }
}

vector<double>& force(const Particule& P, const Boite& B);

#endif
