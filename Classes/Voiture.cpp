#include "Voiture.h"

// ***** Constructeurs ******

Voiture::Voiture()
{
	setNom("Default");
	for (int i = 0; i < 5; ++i)
	{
		options[i] = NULL;
	}
	#ifdef DEBUG
	cout << "est bien passé par le constructeur pas default de voiture" <<  endl;
	#endif
}

Voiture::Voiture(const string n,const Modele m)
{
	for (int i = 0; i < 5; ++i)
	{
		options[i] = NULL;
	}
	setNom(n);
	setModele(m);

	#if DEBUG
	cout << "est bien passé par le constructeur d initialisation de voiture" <<  endl;
	#endif
}

Voiture::Voiture(const Voiture& voiture)
{
	setNom(voiture.getNom());
	setModele(voiture.getModele());
	for (int i = 0; i < 5; ++i)
	{
		if(voiture.options[i] == NULL)
			options[i] = NULL;
		else
			options[i] = new Option(*voiture.options[i]);
	}
	#if DEBUG
	cout << "est bien passé par le constructeur de copie de voiture" <<  endl;
	#endif
}

// ***** Destructeurs ******

Voiture::~Voiture()
{
	for (int i = 0; i < 5; ++i)
	{
		if (options[i] != NULL)
		{
			delete options[i];
		}
	}
	#if DEBUG
	cout << "est bien passé par le destructeur de voiture" <<  endl;
	#endif
}

// ***** getXXX / setXXX ******

string Voiture::getNom() const
{
	return nom;
}

Modele Voiture::getModele() const
{
	return modele;
}

Option* Voiture::getOption(int i)const
{
	return options[i];
}

void Voiture::setNom(string n)
{
	if(n.length()==0) return;
	nom=n;
}

void Voiture::setModele(Modele m)
{
	modele.setNom(m.getNom());
	modele.setPuissance(m.getPuissance());
	modele.setMoteur(m.getMoteur());
	modele.setPrixDeBase(m.getPrixDeBase());
	modele.setImage(m.getImage());
}

// ***** Autres Fonctions ******

void Voiture::Affiche() const
{
	cout <<"Nom Voiture: " << nom << endl;
	modele.Affiche();
	for (int i = 0; i < 5; ++i)
	{
		if(options[i] != NULL)
		{
			options[i]->Affiche();
		}
	}
}

float Voiture::getPrix() const
{
	float PrixTotal = modele.getPrixDeBase();

	for (int i = 0; i < 5; ++i)
	{
		if(options[i] != NULL)
		{
			PrixTotal += options[i]->getPrix();
		}
	}
	return PrixTotal;
}

void Voiture::AjouteOption(const Option& option)
{
	int i = 0, n = -1;

	while(options[i] != NULL && i<5)
	{
		i++;
	}

	if (i<5)
	{
		for(i = 0; i<5; i++)
		{

			if(options[i] != NULL)
			{
				if (options[i]->getCode() == option.getCode())
				{
					throw OptionException("Option deja existante.");
				}
			}
			else
			{
				if (n == -1)
				{
					n = i;
				}
			}
		}
		if (n != -1)
		options[n] = new Option(option);

	}
	else
	{
		throw OptionException("Ce projet contient deja 5 options");
	}
}



void Voiture::RetireOption(string code)
{
	int n = 0;
	for (int i = 0; i < 5; ++i)
	{
		if (options[i] != NULL)
		{
			if (options[i]->getCode()== code)
			{
				delete options[i];
				options[i] = NULL;
				i = 5;
				n = 1;
			}
		}
	}
	if (n == 0) // Il n'a pas trouvé l objet
	{
		throw OptionException("Option inexistante dans ce projet");
	}
}

// ************** Opérateurs d'affectation **************

Voiture& Voiture::operator=(const Voiture& v)
{
	// Est-ce qu'il ne vaut mieux pas mettre nom à NULL avant ? 
	nom = v.getNom();
	setModele(v.getModele());
		// On s'assure que le vecteur est à nul.
	for (int i = 0; i < 5; ++i)
	{
		if (options[i] != NULL)
		{
			delete options[i];
			// Donc pas besoin de mettre option[i] = NULL
		}
	}
		// Ajout d'option
	for (int i = 0; i < 5; ++i)
	{
		if(v.options[i] == NULL)
			options[i] = NULL;
		else
			options[i] = new Option(*v.options[i]);
	}
		cout << "est bien passé par l'opérateur = de voiture" <<  endl;	
	return (*this);
}

// ************** Opérateurs d'addition 1 **************

Voiture Voiture::operator+(const Option& o) const
{
	Voiture v1 = (*this);
	v1.AjouteOption(o); // A vérifier.
	return v1;
}

Voiture operator+(const Option& o, Voiture& v) // On a du enlever Voiture:: pour que ca fonction ? Help 
{                                              // --> normal c'est un opérateur libre (et non membre)
	Voiture v1 = v;
	v1.AjouteOption(o);
	return v1;
}

// ************** Opérateurs de soustraction **************

Voiture Voiture::operator-(const Option& o) const
{
	Voiture v1 = (*this);
	v1.RetireOption(o.getCode()); // A vérifier.
	return v1;
}

Voiture Voiture::operator-(const string s) const
{
	Voiture v1 = (*this);
	v1.RetireOption(s); // A vérifier.
	return v1;
}

// ************** Opérateurs de comparaison **************


int Voiture::CompV(const Voiture& v)const
{
   if (getPrix()<v.getPrix())
    {
        return -1;
    }
    if (getPrix()>v.getPrix())
    {
        return 1;
    }
    return 0;
}



int Voiture::operator<(const Voiture& v)const
{
    return CompV(v) == -1;
}



int Voiture::operator>(const Voiture& v)const
{
    return CompV(v) == 1;
}



int Voiture::operator==(const Voiture& v)const
{
    return CompV(v) == 0;
}


/* ***************** >> et / ou << **********************/
ostream& operator<<(ostream& s, const Voiture& v)
{
	s << "Nom : " << v.nom << endl << "Modele : " << v.getModele() << endl;// << "Option 1 : " << *(v.options[0]) << endl; // << "Option 2 : " << v.getOption(1) << endl << "Option 3 : " << v.getOption(2) << endl << "Option 4 : " << v.getOption(3) << endl << "Option 5 : " << v.getOption(4) << endl;
	for (int i =0; i < 5; i++)
	{
		if (v.options[i] != NULL)
		{
			cout << *(v.options[i]);
		}
	}
	return s;
}


/* ***************** [] ********************************/
Option* Voiture::operator[](int i)
{
	return (*this).getOption(i);
}


/* *************** Fichiers sur disque ****************** */

void Voiture::Save()
{
	string Nom = nom + ".car";
    ofstream fichier1(Nom,ios::out);

	int taille = nom.length();
    fichier1.write((char*)&taille, sizeof(int));
    fichier1.write((char*)nom.data(), taille*sizeof(char));

    modele.Save(fichier1);

    int cpt = 0;
    for (int i = 0; i < 5; i++)
    	if (options[i] != NULL)
    		cpt++;
    fichier1.write((char*)&cpt, sizeof(int));

    for (int i = 0; i < 5; i++)
    {
    	if (options[i] != NULL)
    	{
    		options[i]->Save(fichier1);
    	}
    }
    fichier1.close();
}

void Voiture::Load(string fichier)
{
	ifstream fichier1(fichier,ios::in);

	int taille;
	fichier1.read((char*)&taille,sizeof(int));
	nom.resize(taille);
	fichier1.read((char*)nom.data(),taille*sizeof(char));

	// modele.Load(fichier1); Pourquoi ca ne marche pas ??? 

	modele.Load(fichier1);
	
    int cpt;
	fichier1.read((char*)&cpt,sizeof(int));
	for (int i = 0; i < 5; i++)
	{
		if (i<cpt)
		{
			options[i] = new Option;
			options[i]->Load(fichier1);
		}
		else options[i] = NULL;
	}
	fichier1.close();
}





