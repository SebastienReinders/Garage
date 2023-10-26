#include "Vecteur.h"
#include <stdlib.h>
#include <iostream>
#include "Client.h"
#include "Contrat.h"



template <class T> 
Vecteur<T>::Vecteur()
{
	v = new T[25];
	_size = 0;
	_sizeMax = 25;
}



template <class T> 
Vecteur<T>::Vecteur(int n)
{
	v = new T[n];
	_size = 0;
	_sizeMax = n;
}



template <class T> 
Vecteur<T>::Vecteur(const Vecteur<T> &vecteur)  // JMW
{
	_size = vecteur._size;
	_sizeMax = vecteur._sizeMax;
	v = new T[_sizeMax];

	for(int i = 0; i <= _size; i++)
	{
		v[i] = vecteur.v[i];  // JMW
	}
}


template <class T>
Vecteur<T>::~Vecteur()  // JMW
{
	delete [] v;
}


template <class T>
Vecteur<T>& Vecteur<T>::operator=(const Vecteur<T>& vecteur)  // JMW
{
	//~Vecteur(); // on peut pas faire ça
	//v1 Vecteur(Vecteur &vecteur);

	//return v1;

// JMW
	delete [] v;
	_size = vecteur._size;
	_sizeMax = vecteur._sizeMax;
	v = new T[_sizeMax];

	for(int i = 0; i <= _size; i++)
	{
		v[i] = vecteur.v[i];
	}

	return *this;
}


template <class T>
T& Vecteur<T>::operator[](int ind)
{
	if (ind < 0 && ind >= _size); // throw exception mais pas demandé ici
	return v[ind];  // JMW

    
}



template <class T>
int Vecteur<T>::size()
{
	return _size;
}


template <class T>
int Vecteur<T>::sizeMax()
{
	return _sizeMax;
}


template <class T>
void Vecteur<T>::insere(const T & val)
{
	if(_size < _sizeMax)
	{
		v[_size] = val;  // JMW
		_size++;
	}
	
}


template <class T>
T Vecteur<T>::retire(int ind)
{
	T temp; // = new T; --> JMW : temp n'est pas un pointeur

	if(ind < _size)
	{
		temp = v[ind];
		// delete v[ind] = NULL;   JMW
		for(ind; ind < _size; ind++)
		{
			v[ind] = v[ind + 1];

		}
		_size --;
		// delete v[ind];
	}
	/*else
	{
		return 0;
	}*/


	return temp;
}


template <class T>
void Vecteur<T>::Affiche() const
{
	if(_size > 0)
	{
		for(int i = 0; i < _size; i++)
		{
			cout << v[i] << endl;
		}
	}
	else
	{
		cout << "Vecteur inexistant" << endl;
	}
}


template class Vecteur<int>;
#include "Client.h"
template class Vecteur<Client>;
#include "Modele.h"
template class Vecteur<Modele>;
#include "Option.h"
template class Vecteur<Option>;
#include "Employe.h"
template class Vecteur<Employe>;
#include "Contrat.h"
template class Vecteur<Contrat>;