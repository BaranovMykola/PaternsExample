#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;
class Composit;
class IteratorComposit;

class AbstractInterface
{
public:
	friend class IteratorComposit;
	friend class Composit;
	virtual void show()const = 0;
	virtual void add() {}
	virtual ~AbstractInterface() = default;
private:
	Composit* up;
};

class Composit : public AbstractInterface
{
public:
	friend class IteratorComposit;
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
	string name()const { return mName; }
private:
	string mName;
};

class IteratorComposit : public iterator<input_iterator_tag, Leaf>
{
public:
	IteratorComposit(Composit* root)
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
	Leaf operator->()
	{
		return *dynamic_cast<Leaf*>(nextList.front());
	}
	IteratorComposit operator++()
	{
		nextList.pop();
		operateFirst();
		return *this;
	}
	friend bool operator==(const IteratorComposit left, const IteratorComposit right)
	{
		return left.nextList.front() == right.nextList.front();
	}
	friend bool operator!=(const IteratorComposit left, const IteratorComposit right)
	{
		if (!left.nextList.empty() && !left.nextList.empty()) return true;
		if (!left.nextList.empty() || !left.nextList.empty()) return false;
		return !(left != right);
	}
private:
	queue<AbstractInterface*> nextList;
};