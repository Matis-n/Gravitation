#ifndef Vecteur_hpp
#define Vecteur_hpp

#include <iostream>
using namespace std;

class Vecteur {
	//private:

	public:			
		int dim;
		double* val;
		Vecteur(int dim=2, double x=0.0);
		Vecteur(int dim, int i);
		Vecteur(const Vecteur& P);
		// ~Vecteur(); non nécessaire ici, d'après cpp.developpez.com
		// Si la classe ne contient pas de destructeur par défaut, 
		// alors le compilateur en génère un implicitement.
		// Celui-ci va appeler les destructeurs des différents membres 
		// puis celui des classes parents.
		int dimension() const { return dim; }
		
		void operator+= (const Vecteur& Q);	// ... += Q;
		void operator-= (const Vecteur& Q);	// ... -= Q;
		void operator*= (double x);		// ... *= x;
		void operator/= (double x);		// ... /= x;
		
		bool operator<= (const Vecteur& Q) const;	// P <= Q
		
		// Pour éviter de devoir faire des accèsseurs
		friend Vecteur operator+ (const Vecteur& P, const Vecteur& Q);	// ... = P + Q;
		friend Vecteur operator+ (const Vecteur& P, double x);		// ... = P + x;
		friend Vecteur operator- (const Vecteur& P, const Vecteur& Q);	// ... = P - Q;
		friend Vecteur operator* (double x, const Vecteur& P);		// ... = x * P;
		friend Vecteur operator/ (const Vecteur& P, double x);		// ... = P / x;
		
		friend void Compatible (const Vecteur& P, const Vecteur& Q, const char* origine);
		friend double norme2(const Vecteur& P);
		friend ostream& operator<<(ostream& os, const Vecteur& P);
};

#endif
