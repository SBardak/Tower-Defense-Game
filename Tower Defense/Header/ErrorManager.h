/*

ErrorManager class
-------------------
Static class providing an indirect way of displaying error message. The implementation depends completely on the output used, In that case, we send the standard errors through cout.

*/

#pragma once
#include "IError.h"

class ErrorManager{
public:
	static void DisplayError(IError& err);
};