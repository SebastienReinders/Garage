#ifndef INTERVENANT_H
#define INTERVENANT_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include "Personne.h"
using namespace std;

class Intervenant : public Personne
{



protected:
	int numero;


public:

	static int numCourant;

	Intervenant();
	Intervenant(const string n2, const string pr2, const int n);
	Intervenant(const Intervenant& intervenant);
	~Intervenant();

	virtual string Tuple() = 0;
	virtual string ToString() = 0;
	
	int getNumero() const;


	void setNumero(const int n);


	//void Affiche() const;

	virtual Intervenant& operator=(const Intervenant& intervenant);

	void save(ofstream& fichier1);
	void load(ifstream & fichier1);
};


#endif