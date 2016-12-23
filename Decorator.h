#pragma once
#include "Context.h"
#include <iostream>

using namespace std;

class AbstractDecorator : public Field
{
public:
	virtual void showBuns()const = 0;
	double getReal()const { return mConcreteObject->getReal(); }
	double getImaginary()const { return mConcreteObject->getImaginary(); }
protected:
	Field* mConcreteObject;
};

class Stars : public AbstractDecorator
{
public:
	Field* mConcreteObject;
	Stars(Field* concreteObject)
	{
		AbstractDecorator::mConcreteObject = concreteObject;
	}
	void showBuns()const
	{
		cout << "*" << AbstractDecorator::getReal() << "* and *" << AbstractDecorator::getImaginary() << "i*" << endl;
	}

};
