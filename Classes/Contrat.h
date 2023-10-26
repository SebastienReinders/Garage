#ifndef CONTRAT_H
#define CONTRAT_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include <sstream>

using namespace std;

class Contrat
{
	friend ostream& operator<<(ostream& s, const Contrat& c);

private:
	int IdContrat;
	int IdClient;
	int IdVendeur;
	string NomContrat;


public:

	static int numero;

	Contrat();
	Contrat(const int numContrat, int numClient, int numVendeur, string leContrat);
	Contrat(const Contrat& lecontrat);
	~Contrat();


	int getIdContrat() const;
	int getIdClient() const;
	int getIdVendeur() const;
	string getNomContrat() const;

	void setIdContrat(int n);
	void setIdClient (int n);
	void setIdVendeur (int n);
	void setNomContrat (string nom);


	void save(string fichier);
	void load(string fichier);

	Contrat& operator=(const Contrat& lecontrat);
};


#endif