#pragma once
#include <string>
#include <istream>


using namespace std;

class TraficLight;
class GreenState;
class RedState;

class TraficLight
{
public:
	friend class RedState;
	friend class GreenState;
	class AbstractState
	{
	public:
		virtual bool allow()const = 0;
		virtual void getNext(TraficLight& state) = 0;
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
	TraficLight() = default;
	TraficLight(string name) : mName(name) 
	{
		mCurrentState = new RedState;
	}
	TraficLight(const TraficLight& copy):
		mName(copy.mName)
	{
		mCurrentState = new RedState;
		if (copy.allow())
		{
			update();
		}
	}
	~TraficLight() { delete mCurrentState; }
	bool allow()const
	{
		return mCurrentState->allow();
	}
	void update()
	{
		mCurrentState->getNext(*this);
	}
	string name()const { return mName; }
	TraficLight operator=(const TraficLight& copy)
	{
		delete mCurrentState;
		mCurrentState = new RedState;
		if (copy.allow())
		{
			update();
		}
		return *this;
	}
private:
	string mName;
	AbstractState* mCurrentState;
};

//inline GreenState* getGreen() { return new GreenState; }

//inline RedState* getRed() { return new RedState; }