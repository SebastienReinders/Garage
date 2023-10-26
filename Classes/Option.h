#ifndef OPTION_H
#define OPTION_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
using namespace std;
#include "OptionException.h"
#include <fstream>

class Option
{

	friend ostream& operator<<(ostream& s, const Option& o);
	friend istream& operator>>(istream& s, Option& o);
	
	

private:
	string code;
	string intitule;
	float prix;

public:
	Option();
	Option(const string c, const string i, const float p);
	Option(const Option& option);
	~Option();


	string getCode() const;
	string getIntitule() const;
	float getPrix() const;

	void setCode(const string);
	void setIntitule(const string);
	void setPrix(const float);


	void Affiche() const;

	Option& operator=(const Option& option);

	Option operator--(); // --X
	Option operator--(int); // X--
	
	void Save(ofstream& fichier1) const;
	void Load(ifstream & fichier);



	
};


#endif