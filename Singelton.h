#pragma once

class Singelton
{
public:
	~Singelton() = default;
	static Singelton* getObject()
	{
		return unqieObject;
	}
private:
	Singelton(int value) : data(value) {}
	static Singelton* unqieObject;
	int data;
};


Singelton* Singelton::unqieObject = p;
