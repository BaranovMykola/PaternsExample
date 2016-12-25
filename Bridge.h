#pragma once
#include "Context.h"
#include <iostream>

class AbstractBridge
{
public:
	virtual void square()const = 0;
protected:
	Field* mObject;
};

class SqureField : public AbstractBridge
{
public:
	SqureField(Field* object) { AbstractBridge::mObject = object; }
	void square()const
	{
		double real;
		double imaginary;
		real = pow(mObject->getReal(), 2) - pow(mObject->getImaginary(), 2);
		imaginary = 2 * mObject->getReal()*mObject->getImaginary();
		std::cout << real << " i(" << imaginary << ')';

	}
};	