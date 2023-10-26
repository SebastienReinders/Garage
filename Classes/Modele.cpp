#include "Modele.h"

// ***** Constructeurs ******

Modele::Modele()
{
	nom = NULL;
	setNom("Default");
	setPuissance(0);
	setMoteur(Hybride);
	setPrixDeBase(0.0);
	setImage("2008.jpg");

	cout << "est bien passé par le constructeur pas default de modele" <<  endl;

}

Modele::Modele(const char*n, int p, Moteur m, float pb)
{
	nom = NULL;
	setNom(n);
	setPuissance(p);
	setMoteur(m);
	setPrixDeBase(pb);
	cout << "est bien passé par le constructeur d initialisation de modele" <<  endl;

}



Modele::Modele(const char*n, int p, Moteur m, float pb, string image)
{
	nom = NULL;
	setNom(n);
	setPuissance(p);
	setMoteur(m);
	setPrixDeBase(pb);
	setImage(image);
	cout << "est bien passé par le constructeur d initialisation de modele" <<  endl;

}

Modele::Modele(const Modele& modele)
{
	nom = NULL;
	setNom(modele.getNom());
	setPuissance(modele.getPuissance());
	setMoteur(modele.getMoteur());
	setPrixDeBase(modele.getPrixDeBase());
	setImage(modele.getImage());

	cout << "est bien passé par le constructeur de copie de modele" <<  endl;

}
// ***** Destructeurs *******

Modele::~Modele()
{
	if (nom) delete nom;

	cout << "est bien passé par le destructeur de modele" <<  endl;

}


// ***** gets/ sets ******

char* Modele::getNom() const { return nom; }
int Modele::getPuissance() const { return puissance; }
Moteur Modele::getMoteur() const { return moteur; }
float Modele::getPrixDeBase() const { return PrixDeBase; }

string Modele::getImage() const
{
	return image;
}

void Modele::setNom(const char* n)
{
	if (n == NULL) return;
	if (nom) delete nom;
	nom = new char[strlen(n) + 1];
	strcpy(nom,n);
}

void Modele::setPuissance(int p) 
{ 
	if(p>0)
	{
		puissance = p; 
	}
}

void Modele::setMoteur(Moteur m) 
{ 
	moteur = m;
}
void Modele::setImage(string n)
{
	if(n.length()==0) return;
	image = n;
}

void Modele::setMoteur(string n) 
{ 
	if (n == "Essence")
	{
		moteur = Essence;
	}
		if (n == "Diesel")
	{
		moteur = Diesel;
	}
		if (n == "Hybride")
	{
		moteur = Hybride;
	}
		if (n == "Electrique")
	{
		moteur = Electrique;
	}
}

void Modele::setPrixDeBase(float pb) 
{
	if(pb>=0)
	{
		PrixDeBase = pb;
	}
}

// ***** Affichages *****

void Modele::Affiche() const
{
	if(nom)
		cout << "Nom modele: " << nom << endl;
	else
		cout << "Le nom est indefini" << endl;
	
	cout << "Puissance: " << puissance << endl;
	switch (moteur)
	{
		case 0: cout << "Moteur: " << "Essence " << endl;
		break;
		case 1: cout << "Moteur: " << "Diesel" << endl;
		break;
		case 2: cout << "Moteur: " << "Electrique" << endl;
		break;
		case 3: cout << "Moteur: " << "Hybride" << endl;
		break;
	}

	cout << "Prix de base: " << PrixDeBase << endl;
}

// ********** Opérateurs d'affectation ***************

Modele& Modele::operator=(const Modele& modele)
{
	setNom(modele.getNom());
	setPuissance(modele.getPuissance());
	setMoteur(modele.getMoteur());
	setPrixDeBase(modele.getPrixDeBase());
	setImage(modele.getImage());

	cout << "est bien passé par l'opérateur = de modele" <<  endl;	
	return (*this);
}

/* **************** << & >> ******************** */

ostream& operator<<(ostream& s, const Modele& m)
{
	s << "Nom : " << m.nom << "  Puissance : " << m.puissance << "  Moteur : " << m.moteur << "  Prix de base : " << m.PrixDeBase;
	return s;
}

istream& operator>>(istream& s, Modele& m)
	/*********************************************************
	Attention ne prend pas en paramentre les espaces !!!!
	**********************************************************
	**********************************************************
	*********************************************************/
{
	char *n = new char;
	string mot1;
	int p;
	float pr;
	
				// Alimentation des variables :
	cout << endl << "Nom : ";
	cin >> n;
	//m.nom =NULL; -> déja géré par la fonction setNom
	//m.setNom(n);
	//m.nom = n;
	m.setNom(n);



	cout << endl << "Puissance : ";
	cin >> p;
	//m.setPuissance(p);
	//m.puissance = p;
	m.setPuissance(p);



	cout << endl << "Moteur : ";
	cin >> mot1;
	
	m.setMoteur(mot1);
	//m.moteur = mot1;
	//m.setMoteur(mot1);

//	Essence, Diesel, Electrique, Hybride

	


	cout << endl << "Prix de base : ";
	cin >> pr;
	//m.setPrixDeBase(pr);
	//m.PrixDeBase = pr;
	m.setPrixDeBase(pr);

	return s;
}


/************Surcharge de << et >> pour l'enumeration Moteur***************/
/*
istream& operator>>(istream & s, Moteur mot)
{
	Moteur mot2;

	cin >> mot2;
	mot.setMoteur(mot2);

	return s;
}*/

/* *************** Fichiers sur disque ****************** */

void Modele::Save(ofstream& fichier1) const
{
	float monfloat = getPrixDeBase();
	fichier1.write((char*)&monfloat, sizeof(float));

	int taille = strlen(nom);
	fichier1.write((char*)&taille,sizeof(int));
	fichier1.write(nom, taille * sizeof(char));

	taille = getPuissance();
	fichier1.write((char*)&taille, sizeof(int));
	
	taille = getMoteur();
	fichier1.write((char*)&taille, sizeof(int));

	//cout << "Le prix vaut : " << monfloat << endl<< endl<< endl;

}

 void Modele::Load(ifstream & fichier)
 {
 	int taille;
 	char tmp[80];
 	Moteur mot;
 	float monPrecieux = 100;

 	fichier.read((char*)&monPrecieux, sizeof(float));
	setPrixDeBase(monPrecieux);

 	fichier.read((char*)&taille,sizeof(int));
 	//cout << "Taille vaut : " << taille << endl<< endl<< endl<< endl<< endl<< endl;
 	fichier.read(tmp,taille * sizeof(char));
 	tmp[taille] = 0;
 	//strcat (nom, "\0");
 	setNom(tmp);


	fichier.read((char*)&taille, sizeof(int));
	setPuissance(taille);
	
	fichier.read((char*)&mot, sizeof(int));
	setMoteur(mot);


	//cout << "le prix recherche est : " << monPrecieux << endl<< endl<< endl<< endl;

 }
