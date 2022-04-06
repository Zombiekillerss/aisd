#include <iostream>
#include "Mymap.h"

int main()
{
	int value = 50, key[] = { 55,40,65,60,75,57 };
	Mymap map;
	Listnum maplist;
	for (int i = 0; i < 6; i++) {
		map.insert(key[i], value);
	}
	maplist = map.get_keys();
}
