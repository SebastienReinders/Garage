#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include <iostream>  // Les autres nous ont conseillié de les mettre dans le .h au lieu du CPP
#include <cstring>
#include "Exception.h"
using namespace std;

class PasswordException : public Exception
{
private :
	int code;

public:
	PasswordException();
	PasswordException(string m, int i);
	PasswordException(const PasswordException& passwordException);

	~PasswordException();

	int getPasswordException() const;

	void setPasswordException(int c);

	static const int INVALID_LENGTH;
	static const int ALPHA_MISSING;
	static const int DIGIT_MISSING;
	static const int NO_PASSWORD;
};


#endif