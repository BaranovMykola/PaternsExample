#pragma once
#include <iostream>
#include "Context.h"

class AbstractHandler
{
public:
	virtual void handle(Field* obj) = 0;
protected:
	AbstractHandler* mNext;
};

class HandlerC : public AbstractHandler
{
public:
	HandlerC(AbstractHandler* next) { mNext = next; }
	void handle(Field* obj)
	{
		if (obj->getImaginary() == 0)
		{
			mNext->handle(obj);
		}
		else
		{
	std::cout << "It's Complex" << std::endl;
		}
	}
};

class HandlerR : public AbstractHandler
{
public:
	HandlerR(AbstractHandler* next) { mNext = next; }
	void handle(Field* obj)
	{
		if (obj->getReal() == 0)
		{
			mNext->handle(obj);
		}
		else
		{
			std::cout << "It's Real" << std::endl;
		}
	}
};

class HandlerZero : public AbstractHandler
{
public:
	HandlerZero(AbstractHandler* next) { mNext = next; }
	void handle(Field* obj)
	{
		std::cout << "it's ZERO" << std::endl;
	}
};



