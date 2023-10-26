#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include <sstream>
#include <ctype.h>
#include <fstream>	
#include "Intervenant.h"
#include "PasswordException.h"
using namespace std;

class Employe : public Intervenant
{
	friend ostream& operator<<(ostream& s, const Employe& p);

private:
	string login;
	string* motDePasse;
	string fonction;

public:

	static const string ADMINISTRATIF;
	static const string VENDEUR;

	Employe();
	Employe(const string n2, const string pr, const int n,const string log, string fonc);
	Employe(const Employe& employe);


	~Employe();


	virtual string Tuple();
	virtual string ToString();


	
	string getLogin() const;
	string getFonction() const;
	string getMotDePasse() const;

	void setFonction(const string f);
	void setLogin(const string log);
	void setMotDePasse(const string mdp);
	void ResetMotDePasse();
	int motDePasseExiste() const;

	void save(ofstream& fichier1);
    void Load(ifstream & fichier1);

	virtual Employe& operator=(const Employe& employe);
	
};


#endif