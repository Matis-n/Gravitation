#include <iostream>
#include <cmath>
#include <vector>
#include "gravitation.hpp"

using namespace std;

int main(){

    //Initialisation particules 
    std::list<Particule> liste_particules=initialisation(2);
    printf("0\n");
    Boite B0=init_boite(liste_particules);
    printf("1\n");
/*    maj_positions_vitesses(liste_particules);
    maj_forces(liste_particules,distance_threshold,epsilon,B0);
    */

    return 0;




}
