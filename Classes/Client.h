#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include <sstream>
#include "Intervenant.h"
using namespace std;

class Client : public Intervenant
{
	friend ostream& operator<<(ostream& s, const Client& p);

private:
	string GSM;

public:

	Client();
	Client(const string n2, const string pr2, const int n, string tel);
	Client(const Client& client);
	~Client();

	virtual string Tuple();
	virtual string ToString();

	string getGsm() const;


	void setGsm(const string tel);


	//void Affiche() const;

	virtual Client& operator=(const Client& client);
	
};


#endif