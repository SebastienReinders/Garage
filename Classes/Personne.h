#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
using namespace std;

class Personne
{

	friend ostream& operator<<(ostream& s, const Personne& p);
	friend istream& operator>>(istream& s, Personne& p);

protected:
	string Nom;
	string Prenom;


public:
	Personne();
	Personne(const string n, const string pr);
	Personne(const Personne& personne);
	~Personne();


	string getNom() const;
	string getPrenom() const;

	void setNom(const string n);
	void setPrenom(const string pr);


	//void Affiche() const;

	Personne& operator=(const Personne& personne);

	void Save();
    void Load(string fichier);


	
};


#endif