#include "Contrat.h"
	
	int Contrat::numero = 1;


/*Constructeurs et destructeurs */



	Contrat::Contrat()
	{
		setIdContrat(0);
		setIdClient(0);
		setIdVendeur(0);
		setNomContrat("Nouveau");
	}

	Contrat::Contrat(const int numContrat, int numClient, int numVendeur, string leContrat)
	{
		setIdContrat(numContrat);
		setIdClient(numClient);
		setIdVendeur(numVendeur);
		setNomContrat(leContrat);
	}

	Contrat::Contrat(const Contrat& lecontrat)
	{
		setIdContrat(lecontrat.getIdContrat());
		setIdClient(lecontrat.getIdClient());
		setIdVendeur(lecontrat.getIdVendeur());
		setNomContrat(lecontrat.getNomContrat());
	}
	Contrat::~Contrat()
	{

	}

	/*get et set*/

	int Contrat::getIdContrat() const
	{
		return IdContrat;
	}

	int Contrat::getIdClient() const
	{
		return IdClient;
	}

	int Contrat::getIdVendeur() const
	{
		return IdVendeur;
	}

	string Contrat::getNomContrat() const
	{
		return NomContrat;
	}

	void Contrat::setIdContrat(int n)
	{
		IdContrat = n;
	}

	void Contrat::setIdClient (int n)
	{
		IdClient = n;
	}

	void Contrat::setIdVendeur (int n)
	{
		IdVendeur = n;
	}
	void Contrat::setNomContrat (string nom)
	{
		NomContrat = nom;
	}

	void Contrat::save(string fichier)
	{
		cout << "A faire";
	}

	void Contrat::load(string fichier)
	{
		cout << "A faire";
	}

	ostream& operator<<(ostream& s, const Contrat& p)
	{
		s << "IdContrat :" << p.IdContrat << "IdClient :" << p.IdClient << "IdVendeur :" << p.IdVendeur << "Contrat " << p.NomContrat << endl;
		return s;
	}

	Contrat& Contrat::operator=(const Contrat& lecontrat)
	{
		setIdContrat(lecontrat.getIdContrat());
		setIdClient(lecontrat.getIdClient());
		setIdVendeur(lecontrat.getIdVendeur());
		setNomContrat(lecontrat.getNomContrat());

		return (*this);
	}

