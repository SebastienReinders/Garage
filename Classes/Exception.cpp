#include "Exception.h"


Exception::Exception()
{
	message = "Unknown mistake"; 

	cout << "est bien passé par le constructeur par default d Exception" <<  endl;

}

Exception::Exception(const string m)
{
	message = m; 

	cout << "est bien passé par le constructeur d'initialisation d Exception" <<  endl;

}

Exception::Exception(const Exception& exception)
{
	message = exception.message;

	cout << "est bien passé par le constructeur de copie d Exception" <<  endl;
}

Exception::~Exception()
{
	cout << "est bien passé par le destructeur d Exception" <<  endl;
}

string Exception::getException() const {return message;}

void Exception::setException(string m)
{
	message = m;
}
