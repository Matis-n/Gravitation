#ifndef GRAVITATION_HPP
#define GRAVITATION_HPP
#include <iostream>
#include <cmath>
using namespace std;

//=================================================================================
//                        class Point
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
//                        class Boite
//=================================================================================
class Boite {
    public :
        int level; //niveau
        Point center; //centre de la boîte
        Point center_mass; //centre de masse
        double mass;       //masse
        Point& particule; //pointeur vers une liste de particule
        Boite& fille; //pointeur vers la première boîte fille
        Boite& soeur;//pointeur vers la boîte soeur
};
#endif