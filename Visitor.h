#pragma once
/*
class Composite;
class Leaf;

class AbstractVisitor
{
public:
	virtual void visit(const Leaf&)const = 0;
	virtual void visit(Composite&)const = 0;
};

//#include "Composite.h"

class ConsolePrintVisitor : public AbstractVisitor
{
public:
	void visit(const Leaf& obj)const
	{
		cout << obj.name() << " - " << obj.quantity() << endl;
	}
	void visit(Composite& obj)const
	{
/*		for (unique_ptr<AbstractInterface>& i : obj.getLst())
		{
			AbstractInterface* n = i.get();
			Leaf* a = dynamic_cast<Leaf*>(n);
			Composite* b = dynamic_cast<Composite*>(n);
			if (a)
			{
				visit(*a);
			}
			else
			{
				visit(*b);
			}
		}*//*
	}
};*/

