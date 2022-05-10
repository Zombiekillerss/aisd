#pragma once
#include "MyList.h"
#include <iostream>
#include <fstream>

class Floyd {
public:
	Floyd();
	~Floyd();
	string cheapway(string, string, string);
	void print_matrix();
private:
	struct Elem
	{
		bool isinf = false;
		int value = 0;
		int intermediate = -1;
	};
	Elem** matrix = nullptr;
	MyList<string> namecol;
	size_t size = 0;
	size_t countstr(std::string str, char ch);
	void writefromfile(string);
};