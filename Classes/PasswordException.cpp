#include "PasswordException.h"

	const int PasswordException::INVALID_LENGTH = 1;
	const int PasswordException::ALPHA_MISSING = 2;
	const int PasswordException::DIGIT_MISSING = 3;
	const int PasswordException::NO_PASSWORD = 4;

PasswordException::PasswordException() : Exception::Exception()
{
	code = NO_PASSWORD;
}

PasswordException::PasswordException(string m, int i) : Exception::Exception(m)
{
	/*code = */ PasswordException::setPasswordException(i);
		cout << "dans la classe exc le code vaut : " << PasswordException::getPasswordException() << endl<< endl<< endl<< endl;
		
}

PasswordException::PasswordException(const PasswordException &passwordException) : Exception::Exception(passwordException)
{
	PasswordException::setPasswordException(PasswordException::getPasswordException());

}

PasswordException::~PasswordException()
{
	
}

void PasswordException::setPasswordException(int c)
{

	switch (c)
	{
		case 1 : code = INVALID_LENGTH;
		break;
		case 2 : code = ALPHA_MISSING;
		break;
		case 3 : code = DIGIT_MISSING;
		break;
		case 4 : code = NO_PASSWORD;
		break;
	}

}

int PasswordException::getPasswordException() const
{
	return code;
}