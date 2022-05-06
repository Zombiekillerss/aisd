#include <iostream>
#include "Mymap.h"
#include "HuffmanTree.h"

int main()
{
	HuffmanT huf;
	std::string str = "it is test string";
	std::cout << endl;
	huf.encoding(str);
	std::cout << endl << endl;
	str = "The joys of this life are not its joys, but our fear of ascent into the higher life; the torment of this life is not its torment, but our self-flagellation because of this fear.";
	huf.encoding(str);
	std::cout << endl << endl;
	str = "If a person has not lost the ability to wait for happiness, he is happy. This is happiness.";
	huf.encoding(str);
	return 0;
}
