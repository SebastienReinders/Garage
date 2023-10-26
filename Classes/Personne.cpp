#include "Personne.h"

// ***** Constructeurs ******

Personne::Personne()
{
	setNom ("Nom");
	setPrenom("Prenom");

	cout << "est bien passé par le constructeur par default de personne" <<  endl;

}


Personne::Personne(const string n, const string pr)
{
	setNom(n);
	setPrenom(pr);
	cout << "est bien passé par le constructeur d initialisation de personne" <<  endl;
}

Personne::Personne(const Personne& personne)
{
	setNom(personne.getNom());
	setPrenom(personne.getPrenom());
	cout << "est bien passé par le constructeur de copie de personne" <<  endl;
}



// ***** Destructeurs *******

Personne::~Personne()
{

	cout << "a bien détruit l'objet de type personnes" <<  endl;

}

// ***** gets / sets ******


string Personne::getNom() const {return Nom;}
string Personne::getPrenom() const {return Prenom;}


void Personne::setNom(const string n)
{
	Nom = n;
}


void Personne::setPrenom(const string pr)
{
	Prenom = pr;
}



// ***** Affichage *****

/*void Personne::Affiche() const
{
	cout <<"Nom: " << Nom << endl;
	cout <<"Prenom " << Prenom << endl;
}
*/
// ************* operateurs d affectation **********

Personne& Personne::operator=(const Personne& personne)
	{
		setNom(personne.getNom());
		setPrenom(personne.getPrenom());


		cout << "est bien passé par l operateur = de personnes" <<  endl;

		return (*this);
	}

// ***************** >> & << ****************

ostream& operator<<(ostream& s, const Personne& p)
{
	s << "Nom : " << p.Nom << "  Prenom : " << p.Prenom;
	return s;
}


istream& operator>>(istream& s, Personne& p)
	/*	Attention ne prend pas en paramentre les espaces !!!!
		Getline ??? Ca n'a pas l'air de fonctionner */
{
	string n, pr;

				// Alimentation des variables :
	cout << "Nom : ";
	cin >> n;
	p.setNom(n);
	cout << endl << "Prenom : ";
	cin >> pr ;
	p.setPrenom(pr);

	return s;
}
