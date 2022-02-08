#include "Vecteur.hpp"

// Constructeur d'un vecteur de dimension dim
// chacunes des coordonnées est initialisée à x
Vecteur::Vecteur(int dim, double x) {
	this->dim = dim;
	this->val = new double[dim];
	for(int i=0; i<dim; i++) this->val[i] = x;
}

// Construction du ième vecteur de la base canonique en dimension dim
Vecteur::Vecteur(int dim, int i) {
	this->dim = dim;
	this->val = new double[dim];
	this->val[i-1] = 1.0;
}



// Copie d'un vecteur P
Vecteur::Vecteur(const Vecteur& P) {
	this->dim = P.dim;
	this->val = new double[dim];
	for(int i=0; i<dim; i++) this->val[i] = P.val[i];
}

void Vecteur::operator+= (const Vecteur& Q) {
	for(int i=0; i<dim; i++) this->val[i] += Q.val[i];
}

void Vecteur::operator-= (const Vecteur& Q) {
	for(int i=0; i<dim; i++) this->val[i] -= Q.val[i];
}


void Vecteur::operator*= (double x) {
	for(int i=0; i<dim; i++) this->val[i] *= x;
}

void Vecteur::operator/= (double x) {
	for(int i=0; i<dim; i++) this->val[i] /= x;
}

Vecteur operator+ (const Vecteur& P, const Vecteur& Q) {
	Vecteur R(P);
	R += Q;
	return R;
}

Vecteur operator+ (const Vecteur& P, double x) {
	Vecteur R(P.dim, x);
	R += P;
	return R;
}

Vecteur operator- (const Vecteur& P, const Vecteur& Q) {
	Vecteur R(P);
	R -= Q;
	return R;
}

Vecteur operator* (double x, const Vecteur& P) {
	Vecteur R(P);
	R *= x;
	return R;
}

Vecteur operator/ (const Vecteur& P, double x) {
	Vecteur R(P);
	R /= x;
	return R;
}

// Ligne par ligne, P est il plus petit que Q ?
bool Vecteur::operator<= (const Vecteur& Q) const {
	for (int i=0; i<dim; i++) {
		if (this->val[i] > Q.val[i]) return false;
	}
	return true;
}

// Lève une erreur si les deux Vecteur n'ont pas la même dimension
void Compatible (const Vecteur& P, const Vecteur& Q, const char* origine) {
	if (P.dim != Q.dim) {
		cout << origine << " (" << P << "," << Q <<") dimensions incompatibles";
		exit(-1);
	}
}

// Calcul la norme au carrée de P
double norme2(const Vecteur& P) {
	double q = 0.0;
	for(int i=0; i<P.dim; i++) q += P.val[i]*P.val[i];
	return q;
}

ostream& operator<<(ostream& os, const Vecteur& P) {
	// os << "(";
	// for(int i=0; i<P.dim-1; i++) os << P.val[i] << ", ";
	// os << P.val[P.dim-1] << ")";	
	// os << "(";

	// printing vectors into file
	for(int i=0; i<P.dim-1; i++) os << P.val[i] << " ";
	os << P.val[P.dim-1] ;
	return os;
}
