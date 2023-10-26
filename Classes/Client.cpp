#include "Client.h"



// ***** Constructeurs ******
Client::Client() : Intervenant::Intervenant()
{
	
	setGsm("0499/40.40.40");
	
	cout << "est bien passé par le constructeur par default de client" <<  endl;

}


 Client::Client(const string n2, const string pr2, const int n, string tel): Intervenant::Intervenant(n2, pr2, n)
{
	setGsm(tel);
	
	cout << "est bien passé par le constructeur d initialisation de client" <<  endl;
}


Client::Client(const Client& client) : Intervenant::Intervenant(client)
{
	setGsm(client.getGsm());
}



// ***** Destructeurs *******

Client::~Client()
{

	cout << "a bien détruit l'objet de clients" <<  endl;

}

// ***** gets / sets ******


string Client::getGsm() const {return GSM;}


void Client::setGsm(const string tel)
{
	GSM = tel;
}


string Client::ToString() 
{
	ostringstream s;

	s << "[C" << numero << "]" << " " << Nom << " " << Prenom << GSM; 

	return s.str();
}

string Client::Tuple() 
{

	ostringstream s2;

	s2 << "[C" << numero << "]" << ";" << Nom << ";" << Prenom << ";" << GSM; 

	return s2.str();
}



// ***** Affichage *****


// ************* operateurs d affectation **********

Client& Client::operator=(const Client& client)
{
	Intervenant::operator=(client);
	Client::setGsm(client.getGsm());


	cout << "est bien passé par l operateur = de client" <<  endl;

	return (*this);
}



//*************Operateurs cout << **************

ostream& operator<<(ostream& s, const Client& client2)
{
	//Personne::operator<<(client2);


	s  << "Nom : " << client2.Nom << " - Prenom:" << client2.Prenom << "- Id : " << client2.numero << " - Gsm : " << client2.GSM;
	return s;
}
