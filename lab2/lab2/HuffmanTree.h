#pragma once
#include <iostream>
#include "MyList.h"
#include "Mymap.h"
#include "MyBitArr.h"
using namespace std;

class HuffmanT
{
public:
	std::string getcodestr();
	std::string getdecodestr();
	void encoding(std::string);
	~HuffmanT();
private:
	class NodeT
	{
	public:
		bool iswas = false;
		char symbol;
		int value;
		NodeT* root;
		NodeT* left;
		NodeT* right;
		NodeT(char newsymbol, int newvalue, NodeT* newleft = nullptr, NodeT* newright = nullptr, NodeT* newroot = nullptr)
		{
			root = newroot;
			left = newleft;
			right = newright;
			symbol = newsymbol;
			value = newvalue;
		}
	};
	MyList<NodeT*> listnode;
	Mymap<char, MyBitArr> codesym;
	std::string codestr = "";
	std::string decodedstr = "";
	NodeT* head = nullptr;
	Mymap<char, size_t> countchars(std::string);
	size_t countstr(std::string, char);
};

