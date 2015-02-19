/*

Error class
--------------
Concrete implementation of an error

*/


#pragma once
#include "IError.h"

class Error : public IError{
public:
	Error(std::string message);
	string getMessage() const;

private:
	string message;
};