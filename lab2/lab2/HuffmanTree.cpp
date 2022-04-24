#include "HuffmanTree.h"

void HuffmanT::insert(char newsymbol, int newvalue)
{
	if (!head)
	{
		head = new NodeT(newsymbol, newvalue);
		listnode.push_back(head);
		count++;
	}
	else
	{
		NodeT *current = head;
		while (current->left)
			current = current->left;
		current->left = new NodeT(newsymbol, newvalue);
		listnode.push_back(current->left);
		count++;
	}
}

void HuffmanT::encoding(std::string str)
{
	NodeT* newnode;
	NodeT* minnode = nullptr, *minnodesec = nullptr
		, *savecomparison = nullptr, *savecomparisonsec = nullptr, *current = head;
	size_t i, j;
	if (str.length())
	{
		Mymap<char, size_t> charcountmap = countchars(str);
		MyList<char> listchar = charcountmap.get_keys();
		MyList<size_t> listcount = charcountmap.get_values();
		listnode.clear();
		for (int k = 0; k < listchar.get_size(); k++)
		{
			listnode.push_back(new NodeT(listchar.get_elem(k), listcount.get_elem(k)));
		}
		size_t countelem = listnode.get_size();
		while (listnode.get_size() > 1)
		{
			minnodesec = listnode.get_elem(1);
			savecomparison = minnodesec;
			minnode = listnode.get_elem(0);
			savecomparisonsec = minnode;
			for (i = 2; i < listnode.get_size(); i++)
			{
				savecomparison = listnode.get_elem(i);
				if (savecomparison < minnode && savecomparison != minnodesec)
					minnode = savecomparison;
			}
			for (j = 2; j < listnode.get_size(); j++)
			{
				savecomparisonsec = listnode.get_elem(j);
				if (savecomparisonsec < minnodesec && savecomparisonsec != minnode)
					minnodesec = savecomparisonsec;
			}
			newnode = new NodeT('\0', minnode->value + minnodesec->value);
			minnode = new NodeT(minnode->symbol, minnode->value);
			minnodesec = new NodeT(minnodesec->symbol, minnodesec->value);
			if (minnode < minnodesec)
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
			if (current)
			{
				current->left = minnode;
				current = current->left;
			}
			else
			{
				head = minnode;
				current = head;
			}
			current->left = minnodesec;
			current = current->left;
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
				NodeT* current = savecomparison;
				bool place = false;
				while (countelem > codesym.get_size() && current) 
				{
					while (current->left) 
					{ // moves all the way to the left and adds elements
						arr.addNewBit(0);
						place = false;
						current = current->left;
						if (!current->left && !current->right)
							codesym.insert(current->symbol, arr);
					}
					if (current->right) 
					{
						place = true;
						arr.addNewBit(1);
						current = current->right;
						if (!current->left && !current->right)
							codesym.insert(current->symbol, arr);
						continue;
					}
					else 
					{
						//if (iskeys) list.push_back(current->key);
						//else list.push_back(current->value);
					}
					while (current->root && countelem > codesym.get_size()) 
					{
						current = current->root; // goes to the root
						arr.deletbitend();
						if (current->right) 
						{
							if (!place) 
							{
								arr.addNewBit(1);
								current = current->right;
								place = true;
								break;
							}
						}
						if (current->left) {
							if (place) {
								arr.addNewBit(0);
								current = current->left;
								place = false;
								break;
							}
						}
					}
				}
			}
			else
			{
				arr.addNewBit(0);
				codesym.insert(savecomparison->symbol, arr);
			}
		}
	}
}

HuffmanT::~HuffmanT()
{
	NodeT* current = head;
	while (head)
	{
		head = head->left;
		delete current;
		current = head;
	}
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

bool HuffmanT::NodeT::operator<(NodeT*second)
{
	if (this->value < value)
	{
		return true;
	}
	return false;
}
