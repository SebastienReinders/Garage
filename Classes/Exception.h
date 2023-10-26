#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
using namespace std;

class Exception
{


protected:	// On a vu privé dans le cours mais on n'a pas compris pourquoi du coup on a mis protected
			// qui nous semblait plus logique.
	string message;

public:
	Exception();
	Exception(const string m);
	Exception(const Exception& exception);

	~Exception();

	string getException() const;

	void setException(const string);
	
};


#endif