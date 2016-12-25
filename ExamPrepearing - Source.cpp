#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <set>

#include "Adapter.h"
#include "Facade.h"
#include "Decorator.h"
#include "Bridge.h"
#include "Composite.h"
#include "State.h"
#include "Flyweight.h"
#include "AbstractFactory.h"
#include "Visitor.h"
#include "Singelton.h"
#include "Strategy.h"
#include "ChainOfResponsibility.h"

using namespace std;

class Comp
{
public:
	bool operator()(const Leaf& l, const Leaf& r)
	{
		return l.name() < r.name();
	}
};

class DoNotComp
{
public:
	bool operator()(const char& l, const char& r)
	{
		return false;
	}
};

void split(char* _ch)
{
	cout << endl << endl;
	cout << setw(120) << setfill('*') << '*';
	cout << '\t' << _ch << endl;
	cout << endl;
}

bool isBegin(string str) {	return str == "{"; }
bool isEnd(string str) { return str == "}"; }
pair<string, string> split(string str)
{
	auto result = make_pair(string(), string());
	auto space = find(str.begin(), str.end(), ' ');
	copy(str.begin(), space, back_inserter(result.first));
	copy(++space, str.end(), back_inserter(result.second));
	return result;
}

unique_ptr<Composite> readTreeStruct(unique_ptr<Composite> subRoot, ifstream& stream)
{
	string line;
	string musor;
	getline(stream, line);
	while(!isEnd(line))
	{
		if (isBegin(line))
		{
			getline(stream, line);
			auto newSubRoot = make_unique<Composite>(line);
			subRoot->add(readTreeStruct(move(newSubRoot), stream));
			getline(stream, line);
			if(!stream)
			{
				break;
			}
			continue;
		}
		auto args = split(line);
		subRoot->add(make_unique<Leaf>(args.first, stoi(args.second)));
		getline(stream, line);
	}
	return move(subRoot);
}

unique_ptr<Composite> startRead(ifstream& stream)
{
	auto root = make_unique<Composite>("ROOT");
	return readTreeStruct(move(root), stream);
}



//class Singleton
//{
//public:
//	static Singleton* getInstance()
//	{
//		if (!single)
//		{
//			single = new Singleton(0);
//		}
//			return single;
//	}
//	void method(){ cout << "data: " << mData << endl; }
//	void set(int data) { mData = data; }
//	~Singleton(){}
//private:
//	int mData;
//	static Singleton *single;
//	Singleton(int data) : mData(data) {}
//};

Singelon* Singelon::uniqueObject = nullptr;

void main()
{
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		split("Facade");
		R a(20.1);
		C b(2, 1);
		Facade simlify;
		simlify.show(&a);
		simlify.show(&b);

		split("Decorator");
		Stars decor(&b);
		decor.showBuns();

		split("Bride");
		SqureField sqrt(&b);
		sqrt.square();
		split("Composite");
		unique_ptr<Composite> main = make_unique<Composite>("MAIN", true);
		auto sub1 = make_unique<Composite>("SUB1");
		sub1->add(move(make_unique<Leaf>("sub11")));
		sub1->add(move(make_unique<Leaf>("sub12")));
		auto sub2 = make_unique<Composite>("SUB2");
		sub2->add(move(make_unique<Leaf>("sub21")));
		sub2->add(move(make_unique<Leaf>("sub22")));
		auto sub21 = make_unique<Composite>("SUB21");
		sub21->add(move(make_unique<Leaf>("sub221")));
		sub21->add(move(make_unique<Leaf>("sub222")));
		sub2->add(move(sub21));
		main->add(move(sub1));
		main->add(move(sub2));
		main->show();
		cout << endl;

		
		auto it = find_if(IteratorComposite(main.get()), IteratorComposite(nullptr), [](Leaf val) { return val.name() == "sub21"; });
		(*it).show();
		++it;
		auto t = *it;
		(*it).erase();
		cout << endl;
		main->show();
		main.get()->getLst()[0]->erase();
		cout << endl;
		main->show();
		auto root = make_unique<Composite>("ROOT");
		ifstream compFile("compositeRead.txt");
		auto tree = startRead(compFile);
		tree->show();
		(*find_if(IteratorComposite(tree.get()), IteratorComposite(nullptr), [](Leaf& val) { return val.name() == "CityL2"; })).erase();
		cout << endl;
		tree->show();
			
		split("State");
		vector<TraficLight> lights;
		ifstream file("lights.txt");
		do
		{
			string in;
			file >> in;
			lights.emplace_back(in);
		}
		while(!file.eof());
		srand(time(0));
		for (TraficLight& i : lights)
		{
			if (rand() % 2)
			{
				i.update();
			}
		}
		stable_sort(lights.begin(), lights.end(), [](TraficLight l, TraficLight r) { return r.allow() < l.allow() || !(r.allow() < l.allow()) && r.name() < r.name(); });
		for (auto i : lights)
		{
			cout << i.name() << "\t";
			if (i.allow())
			{
				cout << "Green";
			}
			else
			{
				cout << "Red";
			}
			cout << endl;
		}
		split("Flyweight");
		Text text("I love Olya");
		Horizontal* space = new Horizontal(1);
		Vertical* spaceV = new Vertical(3);
		Horizontal* spaceB = new Horizontal(5);
		text.setFont(space);
		text.draw();
		cout << endl;
		text.setFont(spaceV);
		text.draw();
		cout << endl;
		text.setFont(spaceB);
		text.draw();
		cout << endl;
		delete space;
		delete spaceV;
		delete spaceB;

		split("Abstract Factory");
		AbstractFactory* factory;
		factory = new LinuxFactory;
		try
		{
			auto LinuxButton = factory->createLinux(false);
			LinuxButton->show();
			auto LinuxMemo = factory->createLinux(true);
			LinuxMemo->show();
			auto WinBut = factory->createWindows(false);
			WinBut->display();
			auto WinMemo = factory->createWindows(true);
			WinMemo->display();
		}
		catch (char* error)
		{
			cout << "Error: " << error << endl;
		}
		delete factory;

		split("Visitor for composite");

		LineReadVisitor visitor;
		CountryReadVisitor visitorCountry;
		tree->apply(&visitor);
		auto v = visitor.get();
		sort(v.begin(), v.end(), [](Leaf l, Leaf r) { return l.name() < r.name(); });
		for (auto i : v)
		{
			cout << i.name() << " - " << i.quantity() << endl;
		}
		cout << endl;
		tree->apply(&visitorCountry);
		auto data = visitorCountry.operate();
		auto current = data.begin();
		multimap<string, Leaf>::iterator endRange;
		do
		{
			endRange = data.upper_bound(current->first);
			cout << current->first << endl;
			set<Leaf, Comp> echo;
			for (;current != endRange;++current)
			{
				echo.insert(current->second);
			}
			for (auto i : echo)
			{
				cout << '\t' << i.name() << " - " << i.quantity() << endl;
			}
		}
		while(current != data.end());

		split("Adapter");	
		Adapter adapter(&b); // Complex field
		adapter.mult();

		split("Singleton");
		Singelon* p1 = Singelon::getObject();
		Singelon* p2 = Singelon::getObject();
		cout << p1->get() << " " << p2->get() << endl;
		cout << "Set data to 10" << endl;
		p1->set(10);
		cout << "Check value of both singelton objects" << endl;
		cout << p1->get() << " " << p2->get() << endl;
		delete p1;

		split("Strategy");
		To2Strategy to2;
		To5Strategy to5;
		Arithmetic arithmetic;
		arithmetic.setRules(&to2);
		cout << arithmetic.operate(10) << endl;
		arithmetic.setRules(&to5);
		cout << arithmetic.operate(10) << endl;

		split("Repeat algorithm");
		vector<int> vec = { 1,1,2,1 };
		for (auto i = vec.begin();i != vec.end();)
		{
			if (find(vec.begin(), i, *i) != i)
			{
				i = vec.erase(i);
			}
			else
			{
				++i;
			}
		}
		for (auto i : vec)
		{
			cout << i << " ";
		}
		
		split("Chain of Responsibility");
		HandlerZero z(0);
		HandlerR r(&z);
		HandlerC c(&r);
		c.handle(&C(1, 2));

		split("Set task");
		char* speech = "MrrrrrZra";
		set<char> sp;
		for (int i = 0;i < strlen(speech);++i)
		{
			sp.insert(speech[i]);
		}
		for (auto i : sp)
		{
			cout << i << " ";
		}
		set<char> d;
		set<char> res;
		d.insert('r');
		set_difference(sp.begin(), sp.end(), d.begin(), d.end(), inserter(res, res.end()));
		cout << endl;
		for (auto i : res)
		{
			cout << i;
		}

	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state1, &state2))
	{
		cout << endl << "Memory error" << endl;
	}
	split("End of programm");
	system("pause");
}