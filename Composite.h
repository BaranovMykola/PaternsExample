#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <iterator>
#include <algorithm>

using namespace std;
class Composite;
class IteratorComposite;

class AbstractInterface
{
public:
	friend class IteratorComposite;
	friend class Composite;
	virtual void show()const = 0;
	virtual void add() {}
	virtual void erase(bool = false) = 0;
	virtual ~AbstractInterface() = default;
	virtual vector<unique_ptr<AbstractInterface>>& getLst() = 0;
protected:
	Composite* up;
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
	void erase(bool recursion = false) 
	{
		for (unique_ptr<AbstractInterface>& i : lst)
		{
			if (typeid(*(i.get())) != typeid(Composite))
			{
				//cout << (typeid(i.get())).name() << endl;
				i.reset();
			}
			else
			{
				i->erase(true);
			}
		}
		if (!recursion)
		{
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
	}
private:
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
	void erase(bool = false)
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
private:
	string mName;
	int mQuanity;
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