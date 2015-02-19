/*

Error class
--------------
Interface (abstract class) serving as a guideline for an error in general. Used to indirectly display errors to a user (like a Message Box).

*/


#pragma once
using namespace std;
#include <string>

class IError{
public:
	virtual std::string getMessage() const = 0;
};