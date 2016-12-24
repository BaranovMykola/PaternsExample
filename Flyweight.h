#pragma once
#include <string>
#include <iostream>

using namespace std;

class AbstractFlyWeight
{
public:
	AbstractFlyWeight() = default;
	AbstractFlyWeight(int difference): mDifferecne(difference) {}
	virtual string getDifference()const = 0;
	virtual void setDifference(int) = 0;
protected:
	int mDifferecne;
};

class Horizontal : public AbstractFlyWeight
{
public:
	Horizontal() = default;
	Horizontal(int difference) : AbstractFlyWeight(difference) {}
	string getDifference()const
	{
		string result;
		for (int i = 0;i < mDifferecne;++i)
		{
			result.push_back(' ');
		}
		return result;
	}
	void setDifference(int difference)
	{
		mDifferecne = difference;
	}
};

class Vertical : public AbstractFlyWeight
{
public:
	Vertical() = default;
	Vertical(int difference) : AbstractFlyWeight(difference) {}
	string getDifference()const
	{
		string result;
		for (int i = 0;i < mDifferecne;++i)
		{
			result.push_back('\n');
		}
		return result;
	}
	void setDifference(int difference)
	{
		mDifferecne = difference;
	}
};

class Text
{
public:
	Text() = default;
	Text(string ch) : mCh(ch), mFont(nullptr) {}
	void draw()const
	{
		for (auto i : mCh)
		{
			cout << i;
			if (mFont != nullptr)
			{
				cout << mFont->getDifference();
			}
		}
	}
	void setFont(AbstractFlyWeight* font)
	{
		mFont = font;
	}
private:
	string mCh;
	AbstractFlyWeight* mFont;
};


