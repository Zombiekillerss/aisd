#pragma once
#include <iostream>
#include "MyList.h"
#include "Mymap.h"
#include "MyBitArr.h"
using namespace std;

class HuffmanT
{
public:
	void insert(char, int);
	void encoding(std::string);
	~HuffmanT();
private:
	class NodeT
	{
	public:
		bool operator< (NodeT*);
		char symbol;
		int value;
		NodeT* root;
		NodeT* left;
		NodeT* right;
		bool leftvalue;
		bool rightvalue;
		NodeT(char newsymbol, int newvalue)
		{
			root = nullptr;
			left = nullptr;
			right = nullptr;
			symbol = newsymbol;
			value = newvalue;
			leftvalue = 0;
			rightvalue = 1;
		}
	};
	MyList<NodeT*> listnode;
	Mymap<char, MyBitArr> codesym;
	size_t count = 0;
	NodeT* head = nullptr;
	Mymap<char, size_t> countchars(std::string);
	size_t countstr(std::string, char);
};

