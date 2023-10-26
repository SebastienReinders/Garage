#ifndef OPTIONEXCEPTION_H
#define OPTIONEXCEPTION_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include "Exception.h"
using namespace std;

class OptionException : public Exception
{

public:
	OptionException();
	OptionException(const string m);
	OptionException(const OptionException& optionException);

	~OptionException();

};


#endif