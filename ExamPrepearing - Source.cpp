#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include "Adapter.h"
#include "Facade.h"
#include "Decorator.h"
#include "Bridge.h"

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

	system("pause");
}