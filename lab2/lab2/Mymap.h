#pragma once
#include <stdexcept>
#include "MyList.h"

template<typename T1, typename T2>
class Mymap 
{
public:
	Mymap();
	~Mymap();
	void insert(T1 key, T2 value);
	void remove(T1 key);
	bool contains(T1 key);
	T2 find(T1 key);
	MyList<T1> get_keys();
	MyList<T2> get_values();
	int get_size();
	void clear();
	void print();
	Mymap(const Mymap<T1, T2>&);
	Mymap& operator=(Mymap<T1, T2>);
private:
	class Node 
	{
	public:
		T1 key;
		T2 value;
		bool isblack;
		Node* left;
		Node* right;
		Node* parent;
		Node(T1 newkey, T2 newvalue, bool newcolor = false, Node* newparent = nullptr, Node* newleft = nullptr, Node* newright = nullptr) 
		{
			this->key = newkey;
			this->value = newvalue;
			this->isblack = newcolor;
			this->left = newleft;
			this->right = newright;
			this->parent = newparent;
		}
	};
	Node* head = nullptr;
	int count = 0;
	Node* nill = new Node(0, T2(), true);
	void left_turn(Node* swivel);
	void right_turn(Node* swivel);
};

template<typename T1, typename T2>
inline Mymap<T1, T2>::Mymap()
{
}

template<typename T1, typename T2>
inline Mymap<T1, T2>::Mymap(const Mymap<T1, T2>& map)
{
	Node* oldnill = nill;
	head = map.head;
	count = map.count;
	nill = map.nill;
	MyList<T1> listt1 = get_keys();
	MyList<T2> listt2 = get_values();
	head = nullptr;
	count = 0;
	if (oldnill)
		nill = oldnill;
	else nill = new Node(0, T2(), true);
	for(int i =0;i<listt1.get_size();i++)
		insert(listt1.get_elem(i),listt2.get_elem(i));
}

template<typename T1, typename T2>
Mymap<T1,T2>& Mymap<T1, T2>::operator=(Mymap<T1,T2> map)
{
	head = map.head;
	count = map.count;
	nill = map.nill;
	map.head = nullptr;
	map.count = 0;
	map.nill = nullptr;
	return *this;
}

template<typename T1, typename T2>
Mymap<T1, T2>::~Mymap() 
{
	clear();
	if (nill)
		delete nill;
	nill = nullptr;
}

template<typename T1, typename T2>
void Mymap<T1, T2>::insert(T1 newkey, T2 newvalue) 
{
	Node* current = head;
	int aldcount = count;
	if (!head) 
	{
		head = new Node(newkey, newvalue, true);
		count++;
		head->left = nill;
		head->right = nill;
	}
	else 
	{
		Node* previous = nullptr;
		while (count == aldcount) if (newkey > current->key && current != nill)
		{
			if (current->right && current->right != nill)
			{
				previous = current;
				current = current->right;
			}
			else
			{
				current->right = new Node(newkey, newvalue);
				current->right->parent = current;
				current = current->right;
				current->left = nill;
				current->right = nill;
				count++;
				break;
			}
		}
		else if (newkey != current->key && current != nill)
		{
			if (current->left && current->left != nill)
			{
				previous = current;
				current = current->left;
			}
			else {
				current->left = new Node(newkey, newvalue);
				current->left->parent = current;
				current = current->left;
				current->left = nill;
				current->right = nill;
				count++;
				break;
			}
		}
		else if (newkey == current->key && current == nill)
		{
			current = new Node(newkey, newvalue);
			current->left = nill;
			current->right = nill;
			current->parent = previous;
			count++;
			if (previous)
			{
				if (newkey > previous->key)
					previous->right = current;
				else previous->left = current;
			}
		}
		else throw std::invalid_argument("Keys must be different!!");
		while (current->parent && current->parent->parent && !current->parent->isblack)
		{
			if (current->parent->parent->left == current->parent)
			{
				if (current->parent->parent->right && !current->parent->parent->right->isblack)
				{
					current->parent->isblack = true;
					current->parent->parent->right->isblack = true;
					current->parent->parent->isblack = false;
					current = current->parent->parent;
				}
				if (current->parent)
				{
					if (current->parent->isblack)
						break;
					if (current == current->parent->right)
					{
						left_turn(current);
						current = current->left;
					}
					if (current->parent)
					{
						if (current->parent->isblack)
							break;
						if (current->parent->parent && current->parent->parent->left == current->parent)
						{
							current->parent->isblack = true;
							current->parent->parent->isblack = false;
							right_turn(current->parent);
						}
					}
					else break;
				}
				else break;
			}
			else if (current->parent == current->parent->parent->right && current->parent->parent->right)
			{
				if (current->parent->parent->left && !current->parent->parent->left->isblack)
				{
					current->parent->parent->left->isblack = true;
					current->parent->parent->right->isblack = true;
					current->parent->parent->isblack = false;
					current = current->parent->parent;
				}
				else if (current->parent->parent->left && current->parent->left == current) {
					right_turn(current);
					current = current->right;
				}
				else break;
				if (current->parent && current->parent->parent && current->parent->parent->right == current->parent)
				{
					current->parent->isblack = true;
					current->parent->parent->isblack = false;
					left_turn(current->parent);
				}
			}
			else break;
		}
		while (current->parent)
			current = current->parent;
		head = current;
		head->isblack = true;
	}
}

template<typename T1, typename T2>
void Mymap<T1, T2>::remove(T1 key)
{
	Node* current = head, * remove;
	Node* currentforbalance = nullptr;
	bool isblackremove = false;
	count--;
	if (current) while (current->key != key && current != nill)
	{
		if (key > current->key) 
		{
			current = current->right;
			continue;
		}
		else if (key < current->key) 
		{
			current = current->left;
			continue;
		}
	}
	if (!current)
		throw std::invalid_argument("array is empty!!!!");
	else if (current == nill)
		throw std::invalid_argument("key not found!!!");
	if (current != nill) 
	{
		remove = current;
		isblackremove = remove->isblack;
		if (current->right == nill && current->left == nill) 
		{
			if (current->parent) 
			{
				current = current->parent;
				if (current->left == remove)
					current->left = nill;
				else
					current->right = nill;
				nill->parent = current;
				currentforbalance = nill;
				delete remove;
			}
			else 
			{
				delete head;
				head = nullptr;
				current = head;
				isblackremove = false;
			}
		}
		else if (current->left == nill && current->right) 
		{
			currentforbalance = current->right;
			if (current->parent) 
			{
				current = current->parent;
				if (current->left == remove) 
				{
					current->left = remove->right;
					current->left->parent = current;
				}
				else {
					current->right = remove->right;
					current->right->parent = current;
				}
				delete remove;
			}
			else 
			{
				head = head->right;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->right == nill && current->left) 
		{
			currentforbalance = current->left;
			if (current->parent) 
			{
				current = current->parent;
				if (current->left == remove) 
				{
					current->left = remove->left;
					current->left->parent = current;
				}
				else {
					current->right = remove->left;
					current->right->parent = current;
				}
				delete remove;
			}
			else 
			{
				head = head->left;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->left != nill && current->right != nill && current->left && current->right) 
		{
			current = current->right;
			while (current->left != nill)
				current = current->left;
			currentforbalance = current->right;
			isblackremove = current->isblack;
			if (current->parent == remove)
				currentforbalance->parent = current;
			else 
			{
				current->parent->left = currentforbalance;
				currentforbalance->parent = current->parent;
			}
			if (remove->parent) 
			{
				if (remove->parent->left == remove)
					remove->parent->left = current;
				else
					remove->parent->right = current;
			}
			current->left = remove->left;
			if (remove->left->parent != nill)
				remove->left->parent = current;
			if (current != remove->right)
				current->right = remove->right;
			if (remove->right->parent != nill)
				remove->right->parent = current;
			current->parent = remove->parent;
			if (!remove->parent)
				head = current;
			current->isblack = isblackremove;
			delete remove;
		}
	}
	if (isblackremove && head && currentforbalance) 
	{
		while (currentforbalance->parent) 
		{
			if (currentforbalance->parent->left == currentforbalance) 
			{
				current = currentforbalance->parent->right;
				if (current) 
				{
					if (!current->isblack)
					{
						current->isblack = true;
						current->parent->isblack = false;
						left_turn(current);
						current = currentforbalance->parent->right;
						if (current && current->left && current->right)
						{

							if (current->left->isblack == current->right->isblack && current->left->isblack)
							{
								current->isblack = false;
								currentforbalance = currentforbalance->parent;
							}
						}
						else if (current && current->right && current->right->isblack && current->left != nill)
						{
							current->left->isblack = true;
							current->isblack = false;
							right_turn(current->left);
							current = currentforbalance->parent->right;
						}

					}
					else if (current->left && current->right &&
						current->left->isblack == current->right->isblack && current->left->isblack)
					{
						current->isblack = false;
						currentforbalance = currentforbalance->parent;
					}
					else if (current->right && current->right->isblack && current->left != nill)
					{
						current->left->isblack = true;
						current->isblack = false;
						right_turn(current->left);
						current = currentforbalance->parent->right;
					}
					else if (current->right && current->parent && current->parent->right == current)
					{
						current->isblack = currentforbalance->parent->isblack;
						currentforbalance->parent->isblack = true;
						current->right->isblack = true;
						left_turn(current);
					}
					while (current && current->parent && current != nill)
						current = current->parent;
					if (current != nill)
						head = current;
					currentforbalance = head;
				}
			}
			else 
			{
				current = currentforbalance->parent->left;
				if (current)
				{
					if (!current->isblack)
					{
						if (current->parent->left == current)
						{
							current->isblack = true;
							current->parent->isblack = false;
							right_turn(current);
						}
						current = currentforbalance->parent->left;
						if (current->left && current->left->isblack == current->right->isblack && current->left->isblack)
						{
							current->isblack = false;
							currentforbalance = currentforbalance->parent;
						}
						else if (current && current->right && current->right->isblack && current->right
							&& current->right != nill)
						{
							current->left->isblack = true;
							current->isblack = false;
							left_turn(current->right);
							current = currentforbalance->parent->right;
						}
					}
					else if (current->left && current->left->isblack == current->right->isblack 
						&& current->left->isblack)
					{
						current->isblack = false;
						currentforbalance = currentforbalance->parent;
					}
					else if (current && current->right && current->right->isblack && current->right
						&& current->right != nill)
					{
						current->left->isblack = true;
						current->isblack = false;
						left_turn(current->right);
						current = currentforbalance->parent->right;
					}
					else if (current && current->right && current->parent && current->parent->left == current)
					{
						current->isblack = currentforbalance->parent->isblack;
						currentforbalance->parent->isblack = true;
						current->right->isblack = true;
						right_turn(current);
					}
					while (current && current->parent)
						current = current->parent;
					if(current != nill)
						head = current;
					currentforbalance = head;
				}
			}
			currentforbalance->isblack = true;
		}
	}
	if (nill) nill->parent = nullptr;
}

template<typename T1, typename T2>
inline bool Mymap<T1, T2>::contains(T1 key)
{
	Node* current = head;
	while (current != nill && current)
	{
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else break;
	}
	if (current == nill || !current)
		return false;
	return true;
}

template<typename T1, typename T2>
T2 Mymap<T1, T2>::find(T1 key) 
{
	Node* current = head;
	while (current != nill) 
	{
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else break;
	}
	if (current == nill)
		throw std::invalid_argument("Key not found!!");
	return current->value;
}

template<typename T1, typename T2>
MyList<T1> Mymap<T1, T2>::get_keys() 
{
	if (head)
	{
		MyList<T1> list = MyList<T1>();
		Node* current = head;
		while (count > list.get_size() && current)
		{
			while (current->left != nill && current->left)
			{ // moves all the way to the left and adds elements
				list.push_back(current->key);
				current = current->left;
			}
			if (current->right != nill && current->right)
			{
				list.push_back(current->key);
				current = current->right;
				continue;
			}
			else
			{
				list.push_back(current->key);
			}
			while (current->parent && count > list.get_size())
			{
				current = current->parent; // goes to the root
				if (current->right != nill && current->right)
				{
					if (!list.contains(current->right->key))
					{
						current = current->right;
						break;
					}
				}
				if (current->left != nill && current->left)
				{
					if (!list.contains(current->left->key))
					{
						current = current->left;
						break;
					}
				}
			}
		}
		return list;
	}
	throw out_of_range("the tree does not exist!");
}

template<typename T1, typename T2>
MyList<T2> Mymap<T1, T2>::get_values() 
{
	if (head)
	{
		MyList<T2> list = MyList<T2>();
		MyList<T1> flaglist = MyList<T1>();
		Node* current = head;
		while (count > list.get_size() && current)
		{
			while (current->left != nill && current->left)
			{ // moves all the way to the left and adds elements
				list.push_back(current->value);
				flaglist.push_back(current->key);
				current = current->left;
			}
			if (current->right != nill && current->right)
			{
				list.push_back(current->value);
				flaglist.push_back(current->key);
				current = current->right;
				continue;
			}
			else
			{
				list.push_back(current->value);
				flaglist.push_back(current->key);
			}
			while (current->parent && count > list.get_size())
			{
				current = current->parent; // goes to the root
				if (current->right != nill && current->right)
				{
					if (!flaglist.contains(current->right->key))
					{
						current = current->right;
						break;
					}
				}
				if (current->left != nill && current->left)
				{
					if (!flaglist.contains(current->left->key))
					{
						current = current->left;
						break;
					}
				}
			}
		}
		return list;
	}
	throw out_of_range("the tree does not exist!");
}

template<typename T1, typename T2>
inline int Mymap<T1, T2>::get_size()
{
	return count;
}

template<typename T1, typename T2>
void Mymap<T1, T2>::clear() 
{
	while (head != nill && head)
		remove(head->key);
}

template<typename T1, typename T2>
void Mymap<T1, T2>::print() 
{
	MyList<T1> listkeys;
	MyList<T2> listvalues;
	listkeys = get_keys();
	listvalues = get_values();
	for (int i = 0; i < listkeys.get_size(); i++) 
	{
		cout << "key: " << listkeys.get_elem(i) << "; value: " << listvalues.get_elem(i) << endl;
	}
}

template<typename T1, typename T2>
void Mymap<T1, T2>::left_turn(Node* swivel) 
{
	Node* parent = swivel->parent;
	parent->right = swivel->left;
	if (swivel->left != nill) swivel->left->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent)
		head = swivel;
	else 
	{
		if (parent == parent->parent->left)
			parent->parent->left = swivel;
		else
			parent->parent->right = swivel;
	}
	parent->parent = swivel;
	swivel->left = parent;
}

template<typename T1, typename T2>
void Mymap<T1, T2>::right_turn(Node* swivel)
{
	Node* parent = nullptr;
	parent = swivel->parent;
	parent->left = swivel->right;
	if (swivel->right != nill)
		swivel->right->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent)
		head = swivel;
	else
	{
		if (parent == parent->parent->right)
			parent->parent->right = swivel;
		else
			parent->parent->left = swivel;
	}
	parent->parent = swivel;
	swivel->right = parent;
}
