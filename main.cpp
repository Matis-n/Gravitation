#include <iostream>
#include <cmath>
#include <vector>
#include "gravitation.hpp"
#include <fstream>
using namespace std;
const int Temps=100;

int main(){

    //Initialisation particules 
    std::list<Particule> liste_particules=initialisation(100);

    Boite B0=init_boite(liste_particules);
                

    std::ofstream myfile;
    myfile.open ("example.csv");
    for(int t=0;t<Temps;t++){
        maj_forces(liste_particules,distance_threshold,epsilon,B0);
        printf("oui\n");
        maj_positions_vitesses(liste_particules);
        maj_boites(B0,B0);
        std::list<Particule>::iterator it;
        for ( it=liste_particules.begin();it!=liste_particules.end();it++){

          myfile << it->position.at(0);
          myfile << ",";
          myfile << it->position.at(1);
          myfile << ",";


        }
          myfile << "\n";
      }
      myfile.close();


    return 0;




}
