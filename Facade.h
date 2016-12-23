#pragma once
#include <iostream>
#include "Context.h"

using namespace std;

class Facade
{
public:
	Facade();
	~Facade();
	void show(Field* field)
	{
		cout << field->getReal();
		if (field->getImaginary() != 0)
		{
			cout << "+i(" << field->getImaginary() << ')';
		}
		cout << endl;
	}
};

