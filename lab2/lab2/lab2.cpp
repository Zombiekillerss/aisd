#include <iostream>
#include "Mymap.h"
using namespace std;

int main()
{
	Mymap<int, MyList<bool>> map;
	MyList<bool> t;
	t.push_back(0);
	t.push_back(1);
	t.push_back(0);
	t.push_back(1);
	t.push_back(0);
	t.push_back(1);
	map.insert(1, t);
	return 0;
}
