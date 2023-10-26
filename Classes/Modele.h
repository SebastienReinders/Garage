#ifndef MODELE_H
#define MODELE_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

enum Moteur : char
{
	Essence, Diesel, Electrique, Hybride
};
class Modele
{
	friend ostream& operator<<(ostream& s, const Modele& m);
	friend istream& operator>>(istream& s, Modele& m);


private:
	char* nom;
	int puissance;
	Moteur moteur;
	float PrixDeBase;
	string image;

public:
	Modele();
	Modele(const char* n,int p,Moteur m,float pb);
	Modele(const Modele& modele);


	//constructeurs pour gestion modele + img
	Modele(const char* n,int p,Moteur m,float pb, string image);
	

	~Modele();


	char* getNom() const;
	int getPuissance() const;
	Moteur getMoteur() const;
	float getPrixDeBase() const;
	string getImage() const;

	void setNom(const char* n);
	void setPuissance(int p);
	void setMoteur(Moteur m);
	void setMoteur(string n);
	void setPrixDeBase(float pb);
	void setImage(string img);

	void Affiche() const;

	Modele& operator=(const Modele& modele);

	void Save(ofstream& fichier1) const;
	void Load(ifstream & fichier);

	
	
};


#endif