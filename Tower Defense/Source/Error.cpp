#include "Error.h"

Error::Error(string message){
	this->message = message;
}

string Error::getMessage() const{
	return message;
}