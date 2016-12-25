#pragma once

class Singelon
{
public:
	Singelon(const Singelon&) = delete;
	Singelon& operator=(const Singelon&) = delete;
	static	Singelon*  getObject()
	{
		if (uniqueObject == nullptr)
		{
			uniqueObject = new Singelon(0);
		}
		return uniqueObject;
	}
	void set(int data) { mData = data; }
	int get()const { return mData; }
private:
	Singelon(int data) : mData(data) 
	{
	}
	static Singelon* uniqueObject;
	int mData;
};