#include "Intervenant.h"

int Intervenant::numCourant = 1;



// ***** Constructeurs ******
Intervenant::Intervenant() : Personne::Personne()
{
	
	setNumero(1);
	
	cout << "est bien passé par le constructeur par default d Intervenant" <<  endl;

}

Intervenant::Intervenant(const string n2, const string pr2, const int n) : Personne::Personne(n2, pr2)
{
	setNumero(n);
	
	cout << "est bien passé par le constructeur d initialisation d Intervenant" <<  endl;
}

Intervenant::Intervenant(const Intervenant& intervenant) : Personne::Personne(intervenant)
{
	setNumero(intervenant.getNumero());
	cout << "est bien passé par le constructeur de copie d intervenant" <<  endl;
}


// ***** Destructeurs *******

Intervenant::~Intervenant()
{

	cout << "a bien détruit l'objet de type personnes" <<  endl;

}

// ***** gets / sets ******


int Intervenant::getNumero() const
{
	return numero;
}


void Intervenant::setNumero(const int n)
{
	numero = n;
}




// ***** Affichage *****
		// Sans rien

// ************* operateurs d affectation **********

Intervenant& Intervenant::operator=(const Intervenant& intervenant)
	{

		Personne::operator=(intervenant);
		Intervenant::setNumero(intervenant.getNumero());


		cout << "est bien passé par l operateur = d intervenant" <<  endl;

		return (*this);
	}

void Intervenant::save(ofstream& fichier1)
{
	cout << endl << endl << endl << " -------- Je suis dans intervenant pour le numero " << getNumero() << endl << endl << endl ;
	int taille = getNumero();
    fichier1.write((char*)&taille, sizeof(int));
}

void Intervenant::load(ifstream & fichier1)
{

}