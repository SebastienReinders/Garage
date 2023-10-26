#include "OptionException.h"


OptionException::OptionException() : Exception::Exception()
{
	cout << "est bien passé par le constructeur par default d OptionException" <<  endl;
}

OptionException::OptionException (const string m) : Exception::Exception(m)
{
	cout << "est bien passé par le constructeur d'initialisation d OptionsException" <<  endl;
}

OptionException::OptionException (const OptionException& optionException) : Exception::Exception(optionException)
{
	cout << "est bien passé par le constructeur de copie d OptionException" <<  endl;
}


OptionException::~OptionException()
{
	cout << "est bien passé par le destructeur d OptionException" <<  endl;
}
