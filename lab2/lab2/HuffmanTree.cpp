#include "HuffmanTree.h"

std::string HuffmanT::getcodestr()
{
	return codestr;
}

std::string HuffmanT::getdecodestr()
{
	return decodedstr;
}

void HuffmanT::encoding(std::string str)
{
	NodeT* newnode = nullptr;
	NodeT* minnode = nullptr, *minnodesec = nullptr
		, *savecomparison = nullptr, *savecomparisonsec = nullptr, *current = head;
	size_t i, j;
	if (str.length())
	{
		Mymap<char, size_t> charcountmap = countchars(str);
		MyList<char> listchar = charcountmap.get_keys();
		MyList<size_t> listcount = charcountmap.get_values();
		listnode.clear();
		codesym.clear();
		codestr = "";
		decodedstr = "";
		for (size_t k = 0; k < listchar.get_size(); k++)
		{
			listnode.push_back(new NodeT(listchar.get_elem(k), listcount.get_elem(k)));
		}
		size_t countelem = listnode.get_size();
		while (listnode.get_size() > 1)
		{
			minnodesec = listnode.get_elem(0);
			savecomparison = minnodesec;
			minnode = listnode.get_elem(1);
			savecomparisonsec = minnode;
			for (i = 2; i < listnode.get_size() && minnode->value != 1; i++)
			{
				savecomparison = listnode.get_elem(i);
				if (savecomparison->value < minnode->value && savecomparison != minnodesec)
					minnode = savecomparison;
			}
			for (j = 1; j < listnode.get_size() && minnodesec->value != 1; j++)
			{
				savecomparisonsec = listnode.get_elem(j);
				if (savecomparisonsec->value < minnodesec->value && savecomparisonsec != minnode)
					minnodesec = savecomparisonsec;
			}
			savecomparison = minnode;
			savecomparisonsec = minnodesec;
			newnode = new NodeT('\0', minnode->value + minnodesec->value);
			if (minnode->symbol == '\0')
			{
				minnode = new NodeT(minnode->symbol, minnode->value, minnode->left, minnode->right);
				if (minnode->left)
					minnode->left->root = minnode;
				if (minnode->right)
					minnode->right->root = minnode;
			}
			else minnode = new NodeT(minnode->symbol, minnode->value);
			if (minnodesec->symbol == '\0')
			{
				minnodesec = new NodeT(minnodesec->symbol, minnodesec->value, minnodesec->left
					, minnodesec->right);
				if (minnodesec->left)
					minnodesec->left->root = minnodesec;
				if (minnodesec->right)
					minnodesec->right->root = minnodesec;
			}
			else
				minnodesec = new NodeT(minnodesec->symbol, minnodesec->value);
			if (minnode->value < minnodesec->value)
			{
				newnode->left = minnode;
				newnode->right = minnodesec;
			}
			else
			{
				newnode->left = minnodesec;
				newnode->right = minnode;
			}
			minnode->root = newnode;
			minnodesec->root = newnode;
			listnode.push_back(newnode);
			listnode.removeel(savecomparison);
			listnode.removeel(savecomparisonsec);
		}
		if (listnode.get_size() == 1)
		{
			MyBitArr arr = MyBitArr();
			savecomparison = listnode.get_elem(0);
			if (savecomparison->symbol == '\0')
			{
				current = savecomparison;
				bool place = false;
				while (countelem > codesym.get_size() && current) 
				{
					while (current->left) 
					{ // moves all the way to the left and adds elements
						place = false;
						arr.addNewBit(place);
						current = current->left;
						if (!current->left && !current->right)
						{
							codesym.insert(current->symbol, arr);
							current->iswas = true;
						}
					}
					if (current->right) 
					{
						place = true;
						arr.addNewBit(place);
						current = current->right;
						if (!current->left && !current->right)
						{
							codesym.insert(current->symbol, arr);
							current->iswas = true;
						}
						continue;
					}
					else
					{
						if (!codesym.contains(current->symbol))
						{
							codesym.insert(current->symbol, arr);
							current->iswas = true;
						}
					}
					while (current->root && countelem > codesym.get_size()) 
					{
						current = current->root; // goes to the root
						arr.deletbitend();
						if (current->right) 
						{
							if (!current->right->iswas)
							{
								place = true;
								arr.addNewBit(place);
								current = current->right;
								break;
							}
							else
								current->iswas = true;
						}
					}
				}
			}
			else
			{
				arr.addNewBit(0);
				codesym.insert(savecomparison->symbol, arr);
			}
			for (i = 0; i < str.length(); i++)
			{
				codestr += codesym.find(str[i]).tostring();
				codestr += " ";
			}
			MyList<char> listchar = codesym.get_keys();
			MyList<MyBitArr> listcode = codesym.get_values();
			MyBitArr savecode;
			countelem = 0;
			for (i = 0; i < codestr.length(); i++)
			{
				if (codestr[i] == '1')
				{
					savecode.addNewBit(1);
					countelem++;
					continue;
				}
				else if(codestr[i] == '0')
				{
					savecode.addNewBit(0);
					countelem++;
					continue;
				}
				for (j = 0; j < listcode.get_size(); j++)
				{
					if (listcode.get_elem(j) == savecode)
					{
						decodedstr += listchar.get_elem(j);
						savecode.clear();
						break;
					}
				}
			}
			std::cout << "String: " << str << endl;
			std::cout << "Frequency and code table" << endl;
			for (i = 0; i < listchar.get_size(); i++)
			{
				std::cout << listchar.get_elem(i) << " | ";
				std::cout << listcount.get_elem(i) << " | ";
				std::cout << listcode.get_elem(i).tostring() << ";" << endl;
			}
			std::cout << "Encoding result" << endl;
			std::cout << codestr << endl;
			std::cout << "Decoding result" << endl;
			std::cout << decodedstr << endl;
			std::cout << "Compression ratio" << endl;
			std::cout << str.length() * 8 << " / " << countelem << " = "
				<< (float)((str.length() * 8) / (float)(countelem)) << endl;
		}
	}
	else throw std::invalid_argument("The string cannot be empty!!");
}

HuffmanT::~HuffmanT()
{
}

Mymap<char, size_t> HuffmanT::countchars(std::string str)
{
	Mymap<char, size_t> countmap;
	for (int i = 0; i < str.length(); i++)
	{
		if(!countmap.contains(str[i]))
			countmap.insert(str[i], countstr(str, str[i]));
	}
	return countmap;
}

size_t HuffmanT::countstr(std::string str, char ch)
{
	size_t counts = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ch)
			counts++;
	}
	return counts;
}
