#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>

#include "Visitor.h"

using namespace std;
class Composite;
class IteratorComposite;

class Composite;
class Leaf;

class AbstractVisitor
{
public:
	virtual void visit(const Leaf&) = 0;
	virtual void visit(Composite&) = 0;
};




class AbstractInterface
{
public:
	friend class IteratorComposite;
	friend class Composite;
	virtual void show()const = 0;
	virtual void add() {}
	virtual void erase() = 0;
	virtual ~AbstractInterface() = default;
	virtual vector<unique_ptr<AbstractInterface>>& getLst() = 0;
	virtual void apply(AbstractVisitor*) = 0;
protected:
	Composite* up;
private:
	virtual void _erase() = 0;
};

class Composite : public AbstractInterface
{
public:
	friend class IteratorComposite;
	Composite(string category) : mCategory(category){ }
	Composite(string category, bool) : mCategory(category) { up = nullptr; }
	~Composite() {}
	void add(unique_ptr<AbstractInterface> child)
	{
		lst.push_back(move(child));
		lst.back()->up = this;
	}
	void show()const
	{
		cout << '{' << mCategory << endl;
		for (int i = 0;i < lst.size();++i)
		{
			lst[i]->show();
		}
		cout << '}' << endl;
	}
	vector<unique_ptr<AbstractInterface>>& getLst()
	{
		return lst;
	}
	void erase() 
	{
		_erase();
			if (up != nullptr)
			{
				auto parrent = up;
				auto vectorIterator = find_if(parrent->getLst().begin(), parrent->getLst().end(), [&](unique_ptr<AbstractInterface>& val)
				{
					return val.get() == this;
				});
				parrent->getLst().erase(vectorIterator);
			}
			else
			{
				delete this;
			}
	}
	void apply(AbstractVisitor* v)
	{
		v->visit(*this);
	}
	string category()const { return mCategory; }
private:
	void _erase()
	{	//recursion erases componen without removing it from parrent
		for (unique_ptr<AbstractInterface>& i : lst)
		{
			if (typeid(*(i.get())) != typeid(Composite))
			{
				//cout << (typeid(i.get())).name() << endl;
				i.reset();
			}
			else
			{
				i->_erase();
			}
		}
	}
	vector<unique_ptr<AbstractInterface>> lst;
	string mCategory;
};

class Leaf : public AbstractInterface
{
public:
	Leaf(string name, int quantity=0) : mName(name), mQuanity(quantity) {}
	~Leaf() {}
	void show()const
	{
		cout << mName << " - " << mQuanity << endl;
	}
	void erase()
	{
		auto parrent = up;
		auto vectorIterator = find_if(parrent->getLst().begin(), parrent->getLst().end(), [&](unique_ptr<AbstractInterface>& val) { 
			return val.get() == this;
		});
		parrent->getLst().erase(vectorIterator);
	}
	string name()const { return mName; }
	int quantity()const { return mQuanity; }
	vector<unique_ptr<AbstractInterface>>& getLst()
	{
		return vector<unique_ptr<AbstractInterface>>();
	}
	void apply(AbstractVisitor* v)
	{
		v->visit(*this);
	}
private:
	void _erase() {}
	string mName;
	int mQuanity;
};

class ConsolePrintVisitor : public AbstractVisitor
{
public:
	void visit(const Leaf& obj)
	{
		cout << obj.name() << " - " << obj.quantity() << endl;
	}
	void visit(Composite& obj)
	{
		for (unique_ptr<AbstractInterface>& i : obj.getLst())
		{
			AbstractInterface* n = i.get();
			Leaf* a = dynamic_cast<Leaf*>(n);
			Composite* b = dynamic_cast<Composite*>(n);
			if (a != nullptr)
			{
				visit(*a);
			}
			else
			{
				visit(*b);
			}
		}
	}
};

class LineReadVisitor : public AbstractVisitor
{
public:
	LineReadVisitor() {}
	void visit(const Leaf& obj)
	{
		line.push_back(obj);
	}
	void visit(Composite& obj)
	{
		for (unique_ptr<AbstractInterface>& i : obj.getLst())
		{
			AbstractInterface* n = i.get();
			Leaf* a = dynamic_cast<Leaf*>(n);
			Composite* b = dynamic_cast<Composite*>(n);
			if (a != nullptr)
			{
				visit(*a);
			}
			else
			{
				visit(*b);
			}
		}
	}
	vector<Leaf> get() { return line; }
private:
	vector<Leaf> line;
};

class CountryReadVisitor : public AbstractVisitor
{
public:
	void visit(const Leaf& obj)
	{
		data.insert(make_pair(way, obj));
	}
	void visit(Composite& obj)
	{
		for (unique_ptr<AbstractInterface>& i : obj.getLst())
		{
			AbstractInterface* n = i.get();
			Leaf* a = dynamic_cast<Leaf*>(n);
			Composite* b = dynamic_cast<Composite*>(n);
			way.push_back(obj.category());
			if (a != nullptr)
			{
				visit(*a);
			}
			else
			{
				visit(*b);
			}
			way.pop_back();
		}
	}
	list<string> get() { return way; }
	multimap<list<string>, Leaf> getData() { return data; }
	multimap<string, Leaf> operate()
	{
		multimap<string, Leaf> result;
		string f;
		for (auto i : data)
		{
			if (i.first.size() >= 3)
			{
				f = *next(i.first.begin(), 2);
				Leaf s(i.second.name(), i.second.quantity());
				result.insert(make_pair(f, s));
			}
		}
		return result;
	}
private:
	multimap<list<string>, Leaf> data;
	list<string> way;
};

class IteratorComposite : public iterator<input_iterator_tag, Leaf>
{
public:
	IteratorComposite(Composite* root)
	{
		if (root != nullptr)
		{

			for (int i = 0;i < root->lst.size();++i)
			{
				nextList.push(root->lst[i].get());
			}
			operateFirst();
		}
	}
	void operateFirst()
	{
		if (!nextList.empty())
		{
			while (typeid(*nextList.front()) != typeid(Leaf))
			{
				Composite* subComposite = dynamic_cast<Composite*>(nextList.front());
				for (int i = 0;i < subComposite->lst.size();++i)
				{
					nextList.push(subComposite->lst[i].get());
				}
				nextList.pop();
			}
		}
	}
	Leaf& operator*()
	{
		return *dynamic_cast<Leaf*>(nextList.front());
	}
	Leaf operator->()
	{
		return *dynamic_cast<Leaf*>(nextList.front());
	}
	IteratorComposite operator++()
	{
		nextList.pop();
		operateFirst();
		return *this;
	}
	friend bool operator==(const IteratorComposite left, const IteratorComposite right)
	{
		return left.nextList.front() == right.nextList.front();
	}
	friend bool operator!=(const IteratorComposite left, const IteratorComposite right)
	{
		if (!left.nextList.empty() && !left.nextList.empty()) return true;
		if (!left.nextList.empty() || !left.nextList.empty()) return false;
		return !(left != right);
	}
private:
	queue<AbstractInterface*> nextList;

};

/*

буде листок
буде композіт

Робимо абвстрактного візітора

Робимо композіт, який працює з нашим абстркантим візітором. 

Робимо конкретного візітора : авбстрактного наслідуваний

*/