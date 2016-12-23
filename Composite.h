#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;
class Composit;
class Iterator;

class AbstractInterface
{
public:
	friend class Iterator;
	friend class Composit;
	virtual void show()const = 0;
	virtual void add() {}
	virtual ~AbstractInterface() = default;
	virtual Iterator begin()const = 0;
	virtual Iterator end() = 0;
private:
	Composit* up;
};

class Composit : public AbstractInterface
{
public:
	friend class Iterator;
	Composit(string category) : mCategory(category) {}
	~Composit() {}
	void add(unique_ptr<AbstractInterface> child)
	{
		lst.push_back(std::move(child));
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
	Iterator begin()const
	{
		return Iterator(this);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
private:
	vector<unique_ptr<AbstractInterface>> lst;
	string mCategory;
};

class Leaf : public AbstractInterface
{
public:
	Leaf(string name) : mName(name) {}
	~Leaf() {}
	void show()const
	{
		cout << mName << endl;
	}
	Iterator begin()const
	{
		return Iterator(nullptr);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
private:
	string mName;
};

class Iterator
{
public:
	Iterator(Composit* root)
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
				Composit* subComposit = dynamic_cast<Composit*>(nextList.front());
				for (int i = 0;i < subComposit->lst.size();++i)
				{
					nextList.push(subComposit->lst[i].get());
				}
				nextList.pop();
			}
		}
	}
	Leaf operator*()
	{
		return *dynamic_cast<Leaf*>(nextList.front());
	}
	Iterator operator++()
	{
		nextList.pop();
		operateFirst();
		return *this;
	}
	friend bool operator==(const Iterator left, const Iterator right)
	{
		return left.nextList.front() == right.nextList.front();
	}
private:
	queue<AbstractInterface*> nextList;
};


