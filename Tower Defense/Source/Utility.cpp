#include "Utility.h"

void Utility::getInt(int & n)
{
	bool isValidated = false;
	do{
    string str;
    getline(cin >> ws,str);

    stringstream buffer(str);
    buffer >> n;

    if (!buffer)
    {
        cout << "Invalid input, please try again: ";
        isValidated = false;
		continue;
    }

    if (!buffer.eof())
    {
        cout << "Invalid input, please try again: ";
        isValidated = false;
		continue;
    }

    isValidated = true;
	}while (!isValidated);
}