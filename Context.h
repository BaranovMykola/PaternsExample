#pragma once


class Field
{
public:
	virtual double getReal()const = 0;
	virtual double getImaginary()const = 0;
};

class R : public Field
{
public:
	R() = default;
	R(double real) : mReal(real) {}
	double getReal()const
	{
		return mReal;
	}
	double getImaginary()const
	{
		return 0;
	}
private:
	double mReal;
};

class C : public Field
{
public:
	C() = default;
	C(double real, double imaginary) : mReal(real), mImaginary(imaginary) {}
	double getReal()const
	{
		return mReal;
	}
	double getImaginary()const
	{
		return mImaginary;
	}
private:
	double mReal;
	double mImaginary;
};