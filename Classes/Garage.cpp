#include "Garage.h"

Garage Garage::instance = Garage();

Voiture Garage::projetEnCours = Voiture();

Employe* Garage::EmplEnCours;

Garage::Garage()
{

}

Garage::~Garage()
{

}
		//Fonctions relatives à la classe : Garage
Garage& Garage::getInstance()
{
	return instance;
}

Voiture& Garage::getProjetEnCours()
{
	return projetEnCours;
}

void Garage::resetProjetEnCours()
{
	projetEnCours = Voiture();
}

		//Fonctions relatives à la classe : Modele
void Garage::ajouteModele(const Modele &m)
{
	modeles.insere(Modele(m));
 cout << endl << endl << endl << "Me voici pour Seb" << m.getImage() << endl;
}

void Garage::afficheModelesDisponibles() const
{
	modeles.Affiche();
}

Modele Garage::getModele(int i)
{

	cout << "Je suis dans Garage-GETMODELE ---" << modeles[i].getImage() << endl;
		return modeles[i];
}

void Garage::importeModeles()
{
	string maLigne;

	ifstream fichier1("Modeles.csv",ios::in);
	getline(fichier1, maLigne, '\n');

	cout << maLigne << endl;

	using std::cout;
	while (getline(fichier1, maLigne, '\n'))
	{
		Modele m;
		char str[200];
		string enString;
		const char* sep = ";";

		strcpy (str, maLigne.c_str());
		char* strtoken = strtok(str,sep);


			m.setNom(strtoken);
			strtoken = strtok(NULL, sep);
			m.setPuissance(atoi(strtoken));
			strtoken = strtok(NULL, sep);

	
			if (strcmp(strtoken, "essence") == 0)
			{
				m.setMoteur(Essence);
			}
			if (strcmp(strtoken, "diesel") == 0)
			{
				m.setMoteur(Diesel);
			}
			if (strcmp(strtoken, "hybride") == 0)
			{
				m.setMoteur(Hybride);
			}
			if (strcmp(strtoken, "electrique") == 0)
			{
				m.setMoteur(Electrique);
			}
			strtoken = strtok(NULL, sep);

			//gérer ici l'image
			enString = strtoken;
			m.setImage(enString);
			cout << endl << endl << endl << endl << endl << endl << endl << endl << enString << endl << endl << endl ;

			strtoken = strtok(NULL, sep);
			m.setPrixDeBase(atof(strtoken));

			cout << "Modele : " << m << endl;

			if(modeles.size() < modeles.sizeMax())
			{

					ajouteModele(m);
					//modeles
			}
	}
	fichier1.close();

}

		//Fonctions relatives à la classe : Options
void Garage::ajouteOption(const Option &o)
{
	options.insere(Option(o));
}

void Garage::afficheOptionsDisponibles() const
{
	options.Affiche();
}

Option Garage::getOption(int i)
{
	return options[i];
}

void Garage::importeOptions()
{
	string maLigne;

	ifstream fichier1("Options.csv",ios::in);
	getline(fichier1, maLigne, '\n');

	cout << maLigne << endl;

	using std::cout;
	while (getline(fichier1, maLigne, '\n'))
	{
		Option o;
		char str[200];
		const char* sep = ";";

		strcpy (str, maLigne.c_str());
		char* strtoken = strtok(str,sep);
		o.setCode(strtoken);
		strtoken = strtok(NULL, sep);
		o.setIntitule(strtoken);
		strtoken = strtok(NULL, sep);
		o.setPrix(atof(strtoken));
		cout << "Option : " << o << endl;
	
		if(options.size() < options.sizeMax())
		{
			ajouteOption(o);
		}
	}

	fichier1.close();

}


		//Fonctions relatives à la classe : Client
void Garage::ajouteClient(string nom, string prenom, string gsm)
{
	clients.insere(Client(nom, prenom, Intervenant::numCourant, gsm));
	Intervenant::numCourant++;
}

void Garage::afficheClients() const
{
	clients.Affiche();
}

void Garage::supprimeClientParIndice(int i)
{
	clients.retire(i);
}

void Garage::supprimeClientParNumero(int num)
{
		Iterateur<Client> iter(clients);
	Client temp; 

	int test = 0; 

	iter.reset();
	int i = 0;


	while(!iter.end() && test == 0)
	{

		////
		temp = clients[i];
		////


		if(temp.Intervenant::getNumero() == num)
		{
			test = 1 ;

		}
		else 
		{
			cout << "Dans la boucle avec test = " << test << "et i = " << i << endl;

			iter++; 
			i++; 
		}

	}
	if (test == 1)
	{
		clients.retire(i);
	}
}



		////Fonctions relatives à la classe : Employe
void Garage::ajouteEmploye(string nom, string prenom, string login, string fonction)
{
  employes.insere(Employe(nom, prenom, Intervenant::numCourant, login, fonction));
  Intervenant::numCourant++;
}

void Garage::afficheEmployes() const
{
	employes.Affiche();
}

void Garage::supprimeEmployeParIndice(int i)
{
	employes.retire(i);
}

void Garage::supprimeEmployeParNumero(int num)
{

	Iterateur<Employe> iter(employes);
	Employe temp; 

	int test = 0; 

	iter.reset();
	int i = 0;


	while(!iter.end() && test == 0)
	{

		////
		temp = employes[i];
		////


		if(temp.Intervenant::getNumero() == num)
		{
			test = 1 ;

		}
		else 
		{
			cout << "Dans la boucle avec test = " << test << "et i = " << i << endl;

			iter++; 
			i++; 
		}

	}
	if (test == 1)
	{
		employes.retire(i);
	}
}


Vecteur<Employe>& Garage::getEmployes()
{
		return employes;
}

Vecteur<Client>& Garage::getClients()
{
	return clients;
}

Vecteur<Contrat>& Garage::getContrats()
{
	return contrats;
}


void Garage::save()
{
	string Nom = "Garage.data";
  ofstream fichier1(Nom,ios::out);
  		// Numero intervenant : 
  int intervenant = Intervenant::numCourant;
  cout << "J'écris dans le fichier le numero d intervenant soit : " << Intervenant::numCourant <<  " et intervenant vaut " << intervenant << endl;
  fichier1.write((char*)&intervenant, sizeof(int));
  		//Nombre d employés :
  int NombEmpl = Garage::employes.size();
  cout << "J'écris dans le fichier le nombre d employes soit : " << NombEmpl << endl;
  fichier1.write((char*)&NombEmpl, sizeof(int));
  		// Ajout des employés dans le fichier
  for (int i = 0; i < NombEmpl; i++)
  {
  	Garage::employes[i].save(fichier1);
  }

  /*		//Nombre de clients :
  int NombCli = 987;//Garage::clients.size(); 987 pour tester.
  cout << "J'écris dans le fichier le nombre de clients soit : " << NombCli << endl;
  fichier1.write((char*)&NombCli, sizeof(int));*/

    fichier1.close();
}

void Garage::load(string fichier)
{
	Employe nouveau;
	cout << endl<< endl<< endl<< endl << "Je lis : "<< endl<< endl<< endl;
		ifstream fichier1(fichier,ios::in);
				// Pour intervenant 
		int intervenant;
		fichier1.read((char*)&intervenant,sizeof(int));
		Intervenant::numCourant = intervenant;
		cout << "J'ai lu dans le fichier le numero suivant " << intervenant << " et Intervantnt.num courant vaut : " << Intervenant::numCourant << endl;
				//Nombre d employés
		int NombEmpl;
		fichier1.read((char*)&NombEmpl,sizeof(int));

		cout << "Le fichier contient : " << NombEmpl << " employés" << endl;

				//Je lis les employés du fichier
	  for (int i = 0; i < NombEmpl; i++)
	  {
	  	//Garage::employes[i].Load(fichier1);
	  	nouveau.Load(fichier1);
	  	Garage::ajouteEmploye("ADMIN", "ADMIN",nouveau.getLogin(), nouveau.getFonction());

	  }

	  Garage::employes.Affiche();
	  //afficheEmployes();

/*
				//Nom de clients
		int NombCli; // Il lit bien 987 donc on est perdus ... 
		fichier1.read((char*)&NombCli,sizeof(int));
		cout << "Le fichier contient : " << NombCli << " clients" << endl;


*/
		    fichier1.close();
}



//Fonctions Contrat

void Garage::ajouteContrat(int IdCo, int IdCli, int IdV, string Nom)
{
		contrats.insere(Contrat(IdCo, IdCli, IdV, Nom));		
}

void Garage::afficheContrats() const
{
		contrats.Affiche();
}

void Garage::supprimeContrat(int ind)
{
		contrats.retire(ind);
}