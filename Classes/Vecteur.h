#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include <sstream>
#include <ctype.h>
//#include "Iterateur.h"
using namespace std;

template <class T> 
class Iterateur;   // JMW : declaration de la classe pour qu'elle soit connue

template <class T> 
class Vecteur
{

	protected :
		T* v;
		int _sizeMax;
		int _size;
		
	public :


		Vecteur();
		Vecteur(int n);
		Vecteur(const Vecteur<T>& vecteur);

		~Vecteur();

		int size();
		int sizeMax();

		void Affiche() const;

		void insere(const T & val);

		T retire(int ind);

		Vecteur<T>& operator=(const Vecteur<T>& vecteur);
		T& operator[] (int ind);

		friend class Iterateur<T>;
};



#endif