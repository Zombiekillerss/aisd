#pragma once
#include "MyList.h"
#include <iostream>
#include <fstream>

class Fulkerson
{
public:
	Fulkerson();
	~Fulkerson();
	int maxflow(string pathtofile);
private:
	struct elem
	{
		int index = 0;
		int value = 0;
		bool operator==(elem el)
		{
			return index == el.index && value == el.value;
		}
	};
	int** matrix;
	size_t size;
	MyList<string> namecol;
	MyList<elem> place;
	void writefromfile(string pathtofile);
};