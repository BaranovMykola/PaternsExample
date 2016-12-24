#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include "Adapter.h"
#include "Facade.h"
#include "Decorator.h"
#include "Bridge.h"
#include "Composite.h"
#include "State.h"

using namespace std;

void split(char* _ch)
{
	cout << endl << endl;
	cout << setw(120) << setfill('*') << '*';
	cout << '\t' << _ch << endl;
	cout << endl;
}

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
		split("Composit");
		unique_ptr<Composit> main = make_unique<Composit>("MAIN");
		auto sub1 = make_unique<Composit>("SUB1");
		sub1->add(move(make_unique<Leaf>("sub11")));
		sub1->add(move(make_unique<Leaf>("sub12")));
		auto sub2 = make_unique<Composit>("SUB2");
		sub2->add(move(make_unique<Leaf>("sub21")));
		sub2->add(move(make_unique<Leaf>("sub22")));
		auto sub21 = make_unique<Composit>("SUB21");
		sub21->add(move(make_unique<Leaf>("sub221")));
		sub21->add(move(make_unique<Leaf>("sub222")));
		sub2->add(move(sub21));
		main->add(move(sub1));
		main->add(move(sub2));
		main->show();
		cout << endl;

		auto it = find_if(IteratorComposit(main.get()), IteratorComposit(nullptr), [](Leaf val) { return val.name() == "sub21"; });
		(*it).show();
		++it;
		(*it).show();

		split("State");
		TraficLight light("Street21");
		for (int i = 0;i < 6;++i)
		{
			bool let = light.allow();
			if (let)
			{
				cout << "Green. Go!" << endl;
			}
			else
			{
				cout << "Red. Stop!" << endl;
			}
			light.update();
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