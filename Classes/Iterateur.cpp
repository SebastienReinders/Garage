#include "Iterateur.h"


template <class T> 
Iterateur<T>::Iterateur(Vecteur<T> &v) : monvec(v)
{
	indice = 0;
}

template <class T>
int Iterateur<T>::end()
{
	if (indice == monvec.size())
	{
		return 1;			//si on est a la fin du vecteur, retourne vrai.
	}
	return 0;
}


template <class T>
void Iterateur<T>::reset()
{
	indice = 0;
}


template <class T>
short Iterateur<T>::operator++()
{
	if(!end())
	{
		indice ++;
		return 1;
	}
	return 0;
}


template <class T>
short Iterateur<T>::operator++(int)	//ici le int en parametre ne sert a rien, il permet juste de distinguer la pré et post incrémentation
{
	return operator++();
}


template <class T>					//Pourquoi pas de parametre de retour ? (return present)
Iterateur<T>::operator T () const
{
	return monvec[indice];
}


template <class T>
const T& Iterateur<T>::operator&(void)
{
	return monvec[indice];
}






template class Iterateur<int>;
#include "Client.h"    // JMW : maintenant...
template class Iterateur<Client>;
#include "Employe.h"
template class Iterateur<Employe>;
#include "Modele.h"
template class Iterateur<Modele>;
#include "Option.h"
template class Iterateur<Option>;
#include "Contrat.h"
template class Iterateur<Contrat>;
