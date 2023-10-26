#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include <sstream>
#include <ctype.h>
#include "Vecteur.h"
// #include "Client.h" pas ici, les template .h doivent rester full "génériques"
using namespace std;

template <class T> 
class Iterateur // : public Vecteur JMW : NON !!! un iterateur est une classe à part
{

private:
	Vecteur<T>& monvec; // JMW
	int indice;


public:
	//Iterateur(); JMW : n'a pas de sens, un iterateur est obligatoirement associé à un conteneur
	Iterateur(Vecteur<T>& v);
	//~Iterateur();
	int end();
	void reset();
	short operator++();
	short operator++(int a);
	/*retourne*/ operator T /*C'est un operateur*/ () const; // Les autres nous ont donné le code pour cette
															 // partie mais on n'a pas réellement compris le
															// pourquoi du comment... 
	const T& operator&();



	
};



#endif
