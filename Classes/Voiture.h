#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <cstring>

using namespace std;
#include "Modele.h"
#include "Option.h"
#include "OptionException.h"
#include <fstream>

class Voiture
{

	friend Voiture operator+(const Option& o, Voiture& v);
	friend ostream& operator<<(ostream& s, const Voiture& v);


private:
	string nom;
	Modele modele;
	Option* options[5];

 int CompV(const Voiture& v)const;

public:
	Voiture();
	Voiture(const string n,const Modele m);
	Voiture(const Voiture& voiture);
	~Voiture();
	
	
	string getNom() const;
	Modele getModele() const;
	Option* getOption(int i) const;

	void setNom(const string n);
	void setModele(Modele m);


	void Affiche() const;
	float getPrix() const;
	void AjouteOption(const Option& options);
	void RetireOption(string code);

	Voiture& operator=(const Voiture& v);

	Voiture operator+(const Option& o) const;

	Voiture operator-(const Option& o) const;

	Voiture operator-(const string s) const;


    int operator<(const Voiture& v)const;
    int operator>(const Voiture& v)const;
    int operator==(const Voiture& v)const;

    Option* operator[](int i);

    void Save();
    void Load(string fichier);
};

#endif