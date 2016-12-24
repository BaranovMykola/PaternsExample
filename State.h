#pragma once
#include <string>
#include <istream>


using namespace std;

class TraficLight;
class GreenState;
class RedState;

inline GreenState* getGreen();
inline RedState* getRed();

class AbstractState
{
public:
	virtual bool allow()const = 0;
	virtual void getNext(TraficLight& state) = 0;
};

class TraficLight
{
public:
	friend class RedState;
	friend class GreenState;
	TraficLight() = default;
	TraficLight(string name) : mName(name) 
	{
	}
	bool allow()const
	{
		return mCurrentState->allow();
	}
	void update()
	{
		mCurrentState->getNext(*this);
	}
private:
	string mName;
	AbstractState* mCurrentState;
};

class RedState : public	 AbstractState
{
public:
	bool allow()const { return false; }
	void getNext(TraficLight& obj)
	{
		obj.mCurrentState = new GreenState;
		delete this;
	};
};

class GreenState : public AbstractState
{
public:
	bool allow()const { return true; }
	void getNext(TraficLight& obj)
	{
		obj.mCurrentState = new RedState;
		delete this;

	}
};

inline GreenState* getGreen() { return new GreenState; }

inline RedState* getRed() { return new RedState; }