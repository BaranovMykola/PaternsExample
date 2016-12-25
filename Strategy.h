#pragma once


class AbstractStrategy
{
public:
	virtual double mult(double a)const = 0;
};

class Arithmetic
{
public:
	double operate(double a)const
	{
		return mStrategy->mult(a);
	}
	void setRules(AbstractStrategy* strategy) { mStrategy = strategy; }
private:
	AbstractStrategy* mStrategy;
};


class To2Strategy : public AbstractStrategy
{
public:
	double mult(double a)const
	{
		return a * 2;
	}
};

class To5Strategy : public AbstractStrategy
{
public:
	double mult(double a)const
	{
		return a * 5;
	}
};