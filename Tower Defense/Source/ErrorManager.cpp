#include "ErrorManager.h"
#include <iostream>

void ErrorManager::DisplayError(IError& err){
	cout << endl << err.getMessage() << endl << endl;
}