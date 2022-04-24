#include <iostream>
#include "Mymap.h"
#include "HuffmanTree.h"
using namespace std;

int main()
{
	HuffmanT huf;
	std::string str = "lollll";
	std::cout << str.length();
	huf.encoding(str);
	return 0;
}
