#include <iostream>
#include <cmath>
#include "gravitation.hpp"
using namespace std;

int main(){
    Point P(0,0);
    Boite B(P,0);
    Point P1(1,1);
    Particule part(P1,3);
    B.ajouter(part);
    return 0;
}
