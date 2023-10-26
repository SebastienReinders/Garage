#include "Employe.h"

const string Employe::ADMINISTRATIF = "Administratif";
const string Employe::VENDEUR = "Vendeur";

// ***** Constructeurs ******
Employe::Employe() : Intervenant::Intervenant()
{
	
	setLogin("sonLogin");
	setFonction("Administratif");
	motDePasse = NULL;
	
	cout << "est bien passé par le constructeur par default d employe" <<  endl;

}


 Employe::Employe(const string n2, const string pr, const int n, const string log, string fonc): Intervenant::Intervenant(n2, pr, n)
{
	setLogin(log);
	setFonction(fonc);
	motDePasse = NULL;
	
	cout << "est bien passé par le constructeur d initialisation d employe" <<  endl;
}


Employe::Employe(const Employe& employe) : Intervenant::Intervenant(employe)
{
	setLogin(employe.getLogin());
	setFonction(employe.getFonction());

	if (employe.motDePasse != NULL)
	{
		setMotDePasse(employe.getMotDePasse());
	}

}



// ***** Destructeurs *******

Employe::~Employe()
{

	cout << "a bien détruit l'objet d employe" <<  endl;

}

// ***** gets / sets ******


string Employe::getLogin() const {return login;}


void Employe::setLogin(const string log)
{
	login = log;
}

void Employe::setFonction(const string f)
{
	if (f == "ADMINISTRATIF" || f == "Administratif" ||f == "administratif")
	{
		fonction = ADMINISTRATIF;
	}
	if (f== "VENDEUR" || f == "Vendeur" || f == "vendeur")
	{
		fonction = VENDEUR;
	}
}

string Employe::getFonction() const {return fonction;}

string Employe::getMotDePasse() const
{
	if (motDePasse != NULL)
	{
		string mdp = *motDePasse;
		return mdp;
	}
	else
	{
		throw PasswordException("Mot de passe inexistant", 4);
	}
	
	return "";
}

void Employe::setMotDePasse(const string mdp)
{
	if (mdp.length() < 6)
	{
		throw PasswordException("Mot de passe doit contenir min 6 caracteres.", 1);
	}
	else
	{
		const char* ptr1 = 0;
		int longeur = mdp.length();
		char* ptr2 = new char[longeur+1];
		ptr1 = mdp.data();
		mdp.copy(ptr2,longeur,0);
		ptr2[longeur] = 0;
		int i, n = 0;


		for (i = 0; i < longeur; i++)
		{
			if (isdigit(ptr2[i]))
			{
				n++;
			}
		}

		if (n == 0)
		{
			throw PasswordException("Mot de passe doit contenir min 1 chiffre", 3);
		}
		n = 0;
		for (i = 0; i < longeur; i++)
		{
			if (isalpha(ptr2[i]))
			{
				n++;
			}
		}

		if (n == 0)
		{
			throw PasswordException("Mot de passe doit contenir min une lettre.", 2);
		}
	}


	if (motDePasse != NULL)
	{
		Employe::ResetMotDePasse();
	}


	motDePasse = new string(mdp);
}

void Employe::ResetMotDePasse()
{
		if (motDePasse != NULL)
	{
		delete motDePasse;
		motDePasse = NULL;
	}

}

int Employe::motDePasseExiste() const
{
	if (motDePasse != NULL)
	{
		return 1;
	}

	return 0;
}

string Employe::ToString() 
{
	ostringstream s;

	s << "[C" << numero << "]" << " " << Nom << " " << Prenom << login << " " << motDePasse << " " << fonction; 

	return s.str();
}

string Employe::Tuple() 
{

	ostringstream s2;

	s2 << "[E" << numero << "]" << ";" << Nom << ";" << Prenom << ";" << fonction << ";" << motDePasse << ";" << login; 

	return s2.str();
}


//*************Operateurs cout << **************

ostream& operator<<(ostream& s, const Employe& employe)
{	

	s  << "Nom : " << employe.Nom << " - Prenom:" << employe.Prenom << "- Id : " << employe.numero << " - Login : " << employe.login <<  " -Fonction : " << employe.getFonction() <<" -Mot de passe : ";
	if (employe.motDePasse != NULL)
	cout <<"Mot de passe" << employe.getMotDePasse() ;
	return s;
}

//***********Operateur == ********************

Employe& Employe::operator=(const Employe& employe)
{
	Intervenant::operator=(employe);
	Employe::setLogin(employe.getLogin());
	if (employe.motDePasse != NULL)
	{
		Employe::setMotDePasse(employe.getMotDePasse());
	}

	Employe::setFonction(employe.getFonction());


	cout << "est bien passé par l operateur = d Employe" <<  endl;

	return (*this);
}

/************************ SAVE ET LOAD ****************************/

void Employe::save(ofstream& fichier1)
{
	this->Intervenant::save(fichier1);
  int vrai;

  	int taille = login.length();
    fichier1.write((char*)&taille, sizeof(int));
    fichier1.write((char*)login.data(), taille*sizeof(char));
    cout << "j'ai écrit Login : " << login.data() << "pour une taille de " << taille << endl;

    if (motDePasse == NULL)
    {
    	vrai = 0;
    }
    else
    {
    	vrai = 1;
    }
    fichier1.write((char*)&vrai, sizeof(int));

    if (vrai == 1)
    {
    	string mdp = getMotDePasse();
        taille = mdp.length();
	    fichier1.write((char*)&taille, sizeof(int));
	    fichier1.write((char*)mdp.data(), taille*sizeof(char));	
    }

    taille = fonction.length();
    fichier1.write((char*)&taille, sizeof(int));
    fichier1.write((char*)fonction.data(), taille*sizeof(char));

}
   
void Employe::Load(ifstream & fichier1)
{
	this->Intervenant::load(fichier1);
	int taille;
	int vrai;
	string mdp;
	string maVariable;

	fichier1.read((char*)&taille,sizeof(int));
	login.resize(taille);
	fichier1.read((char*)login.data(),taille*sizeof(char));
	cout << "j'ai lu login :" << login.data() << " pour une taille de " << taille << endl;
	setLogin(login);
	fichier1.read((char*)&vrai,sizeof(int));
	if (vrai == 1)
	{
		cout << "vrai vaut " << vrai << "donc il y a un mot de passe" << endl;
	fichier1.read((char*)&taille,sizeof(int));
	mdp.resize(taille);
	fichier1.read((char*)mdp.data(),taille*sizeof(char));
	setMotDePasse(mdp);
	}

	fichier1.read((char*)&taille,sizeof(int));
	fonction.resize(taille);
	fichier1.read((char*)fonction.data(),taille*sizeof(char));
	setFonction(fonction);

}