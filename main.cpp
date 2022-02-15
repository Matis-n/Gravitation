#include <iostream>
#include <cmath>
#include "gravitation.hpp"
using namespace std;

int main(){
    Point P(0,0); 
    Point P1(1,1);
    Boite B1 (P,0); //création première grosse boîte de level 0
    Particule p (P1,1.);
    B1.ajouter(p);
    return 0;
}
