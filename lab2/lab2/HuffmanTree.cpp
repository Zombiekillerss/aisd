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
	rsize_t i, j;
	rsize_t countelem = listnode.get_size();
	Mymap<char, MyBitArr> map;
	while (current->left)
		current = current->left;
	while (listnode.get_size() > 1)
	{
		minnodesec = listnode.get_elem(1);
		minnode = listnode.get_elem(0);
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
		newnode->leftvalue = 0;
		newnode->rightvalue = 1;
		minnode->root = newnode;
		minnodesec->root = newnode;
		current->left = minnode;
		current = current->left;
		current->left = minnodesec;
		current = current->left;
		listnode.push_back(newnode);
		listnode.remove(savecomparison);
		listnode.remove(savecomparisonsec);
	}
	if (listnode.get_size() == 1)
	{
		MyBitArr arr = MyBitArr();
		savecomparison = listnode.get_elem(0);
		if (savecomparison->symbol == '\0')
		{
			/*/NodeT* current = savecomparison;
			while (count > list.get_size() && current) {
				while (current->left != nill && current->left) { // moves all the way to the left and adds elements
					if (iskeys) list.push_back(current->key);
					else list.push_back(current->value);
					current = current->left;
				}
				if (current->right != nill && current->right) {
					if (iskeys) list.push_back(current->key);
					else list.push_back(current->value);
					current = current->right;
					continue;
				}
				else {
					if (iskeys) list.push_back(current->key);
					else list.push_back(current->value);
				}
				while (current->parent && count > list.get_size()) {
					current = current->parent; // goes to the root
					if (current->right != nill && current->right) {
						if (iskeys) {
							if (!list.contains(current->right->key)) {
								current = current->right;
								break;
							}
						}
						else if (!list.contains(current->right->value)) {
							current = current->right;
							break;
						}
					}
					if (current->left) {
						if (iskeys) {
							if (!list.contains(current->left->key)) {
								current = current->right;
								break;
							}
						}
						else if (!list.contains(current->left->value)) {
							current = current->right;
							break;
						}
					}
				}
			}
			list.save_list();*/
		}
		else
		{
			map.insert(savecomparison->symbol, arr);
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
	}
}

bool HuffmanT::NodeT::operator<(NodeT*second)
{
	if (this->value < value)
	{
		return true;
	}
	return false;
}
