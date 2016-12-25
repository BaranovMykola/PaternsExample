#pragma once
#include <vector>
#include <iostream>

#include "Context.h"

using namespace std;

class AbstractAdapter
{
public:
	virtual void mult()const = 0;
};

class Adapter : public AbstractAdapter
{
public:
	Adapter(Field* adaptee) : mAdaptee(adaptee) {}
	void mult()const
	{
		cout << mAdaptee->getReal() * 2 << " + i" << mAdaptee->getImaginary() * 2 << endl;
	}
private:
	Field* mAdaptee;
};
