#pragma once
#include <iostream>
#include <memory>

using namespace std;

class WidgetWindows
{
public:
	virtual void display()const = 0;
};

class WinButton : public WidgetWindows
{
public:
	void display()const { cout << "Push me by the window" << endl; }
};

class WinMemo : public WidgetWindows
{
public:
	void display()const { cout << "Input me fully in the window" << endl; }
};

class WidgetLinux
{
public:
	virtual void show()const = 0;
};

class LinuxButton : public WidgetLinux
{
public:
	void show()const { cout << "I'm penguins button" << endl; }
};

class LinuxMemo : public WidgetLinux	
{
public:
	void show()const { cout << "What do you tkink about penguins?" << endl; }
};

class AbstractFactory
{
public:
	virtual unique_ptr<WidgetLinux> createLinux(bool)const = 0;
	virtual unique_ptr<WidgetWindows> createWindows(bool)const = 0;
};

class WinFactory : public AbstractFactory
{
public:
	unique_ptr<WidgetWindows> createWindows(bool butt)const
	{
		if (butt)
		{
			return make_unique<WinButton>();
		}
		else
		{
			return make_unique<WinMemo>();
		}
	}
	unique_ptr<WidgetLinux> createLinux(bool)const
	{
		throw "PENGUINS!!!!!!!!!!!!!!!!!!!!!";
	}
};

class LinuxFactory : public AbstractFactory
{
public:
	unique_ptr<WidgetLinux> createLinux(bool butt)const
	{
		if (butt)
		{
			return make_unique<LinuxButton>();
		}
		else
		{
			return make_unique<LinuxMemo>();
		}
	}
	unique_ptr<WidgetWindows> createWindows(bool)const
	{
		throw "WINDOWS!!!!!!!!!!!!!!!!!!!!!!!";
	}
};
