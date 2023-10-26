#include "Option.h"

// ***** Constructeurs ******

Option::Option()
{
	setCode("0000");
	setIntitule("Default");
	setPrix(0);

	cout << "est bien passé par le constructeur par default d option" <<  endl;

}

Option::Option(const string c,const string i,const float p)
{
	setCode(c);
	setIntitule(i);
	setPrix(p);

	cout << "est bien passé par le constructeur d initialisation d option" <<  endl;

}

Option::Option(const Option& option)
{
	setCode(option.getCode());
	setIntitule(option.getIntitule());
	setPrix(option.getPrix());

	cout << "est bien passé par le constructeur de copie d option" <<  endl;

}


// ***** Destructeurs *******

Option::~Option()
{

	cout << "est bien passé par le destructeur d option" <<  endl;

}

// ***** gets / sets ******

string Option::getCode() const{return code;}
string Option::getIntitule() const {return intitule;}
float Option::getPrix() const {return prix;}


void Option::setCode(string c) //throw (OptionException)
{

	if(c.length()!=4)
	{
		throw OptionException("Le code option doit avoir 4 caracteres");
	}
	code = c;

}

void Option::setIntitule(string i) //throw (OptionException)
{
	if(i.length()==0)
	{
		throw OptionException("L'intitule ne peut etre vide");
	}
	intitule = i;
}

void Option::setPrix(float p) //throw (OptionException)
{
	if(p < 0)
	{
		throw OptionException("Le prix doit etre supperieur a 0");
	}
	prix = p;
}



// ***** Affichage *****

void Option::Affiche() const
{
	cout <<"Code Option: " << code << endl;
	cout <<"Intitule Option: " << intitule << endl;
	cout <<"Prix Option: " << prix << endl;
}

// ************* operateurs d affectation **********

Option& Option::operator=(const Option& option)
	{
		setCode(option.getCode());
		setIntitule(option.getIntitule());
		setPrix(option.getPrix());

		cout << "est bien passé par l operateur = d option" <<  endl;

		return (*this);
	}

// ***************** >> & << ****************

ostream& operator<<(ostream& s, const Option& o)
{
	s << "Code : " << o.code << "  Intitule : " << o.intitule << "  Prix : " << o.prix;
	return s;
}

istream& operator>>(istream& s, Option& o)
	/*	Attention ne prend pas en paramentre les espaces !!!!
		Getline ??? Ca n'a pas l'air de fonctionner */
	//Erreurs déjà gérés dans les setteurs
{
	string c, i;
	float p;
				// Alimentation des variables :
	cout << "Code option : ";
	cin >> c;
	o.setCode(c);
	cout << endl << "Intitule option : ";
	cin >> i ;
	o.setIntitule(i);
	cout << endl << "Prix option : ";
	cin >> p;
	o.setPrix(p);
	return s;
}


/* ********************** -- & ++ ************************/

Option Option::operator--() //throw (OptionException) // --X
{
	if (prix < 50)
		throw OptionException("Le prix ne peut pas etre negatif");
	prix = prix - 50.0;
	return (*this);
}

Option Option::operator--(int) // X--
{
	Option temp (*this);
	if (prix < 50)
		throw OptionException("Le prix ne peut pas etre negatif");
	prix = prix - 50.0;
	return temp;
}


/* *************** Fichiers sur disque ****************** */

void Option::Save(ofstream& fichier1) const
{
	int taille;
	float monPrix;
	string chaine;
	string code = getCode();

	taille = code.size();
	fichier1.write((char*)&taille, sizeof(int));
	fichier1.write((char*)code.data(),sizeof(char)*4);

	monPrix = getPrix();
	fichier1.write((char*)&monPrix, sizeof(float));

	chaine = getIntitule();
	taille = chaine.size();
	fichier1.write((char*)&taille,sizeof(int));
	fichier1.write((char*)chaine.data(), taille);
}

 void Option::Load(ifstream & fichier)					//on charge les donnees depuis le fichier
 {
 	int taille;
 	float monPrix;
 
    fichier.read((char*)&taille,sizeof(int));
    code.resize(taille);
	fichier.read((char*)code.data(),4*sizeof(char));

	fichier.read((char*)&monPrix, sizeof(float));
	setPrix(monPrix);

	fichier.read((char*)&taille,sizeof(int));
	intitule.resize(taille);
	fichier.read((char*)intitule.data(), taille);
 }
