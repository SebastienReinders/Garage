#ifndef GARAGE_H
#define GARAGE_H

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "Vecteur.h"
#include "Employe.h"
#include "Client.h"
#include "Modele.h"
#include "Option.h"
#include "Voiture.h"
#include "Iterateur.h"
#include "Intervenant.h"
#include "Contrat.h"


class Garage
{
	private:
		Vecteur<Employe> employes;
		Vecteur<Client> clients;
		Vecteur<Modele> modeles;
		Vecteur<Option> options;
		Vecteur<Contrat> contrats;

		static Garage instance; 

		Garage();// constructeur par défaut 

		Garage (const Garage & );

		~Garage(); // destructeur 

		Garage & operator=(const Garage &);

		static Voiture projetEnCours;



	public:


		static Employe* EmplEnCours;
		
		static Garage& getInstance();
		static Voiture& getProjetEnCours();
		static void resetProjetEnCours();



		void ajouteModele(const Modele &m);
		void afficheModelesDisponibles() const;
		Modele getModele(int indice);
		void importeModeles();

		void ajouteOption(const Option &o);
		void afficheOptionsDisponibles() const;
		Option getOption(int indice);
		void importeOptions();


		void ajouteClient(string nom, string prenom, string gsm);
		void afficheClients() const;
		void supprimeClientParIndice(int ind);
		void supprimeClientParNumero(int num);
		Vecteur<Client>& getClients();

		void ajouteEmploye(string nom, string prenom, string login, string fonction);
		void afficheEmployes() const;
		void supprimeEmployeParIndice(int ind);
		void supprimeEmployeParNumero(int num);
		Vecteur<Employe>& getEmployes();


		void ajouteContrat(int IdCo, int IdCli, int IdV, string Nom);
		void afficheContrats() const;
		void supprimeContrat(int ind);
		Vecteur<Contrat>& getContrats();

		void save();
		void load(string fichier);
};

#endif