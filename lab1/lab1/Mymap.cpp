#include "Mymap.h"

Mymap::~Mymap() {
	clear();
	delete nill;
	nill = nullptr;
}

void Mymap::insert(int newkey, int newvalue) {
	Node* current = head;
	count++;
	if (!head) {
		head = new Node(newkey, newvalue, true);
		head->left = nill;
		head->right = nill;
	}
	else {
		while (true) if (newkey > current->key && current != nill) {
			if (current->right && current->right != nill)
				current = current->right;
			else {
				current->right = new Node(newkey, newvalue);
				current->right->parent = current;
				current = current->right;
				current->left = nill;
				current->right = nill;
				break;
			}
		}
		else if ((newkey != current->key && current != nill) || (newkey == current->key && current == nill)) {
			if (current->left && current->left != nill)
				current = current->left;
			else {
				current->left = new Node(newkey, newvalue);
				current->left->parent = current;
				current = current->left;
				current->left = nill;
				current->right = nill;
				break;
			}
		}
		else throw std::invalid_argument("Keys must be different!!");
		while (current->parent)
			if (current->parent->parent && !current->parent->isblack) {
				if (current->parent->parent->left == current->parent) {
					if (current->parent->parent->right)
						if (!current->parent->parent->right->isblack) {
							current->parent->isblack = true;
							current->parent->parent->right->isblack = true;
							current->parent->parent->isblack = false;
							current = current->parent->parent;
						}
					if (current->parent) {
						if (current->parent->isblack)
							break;
						if (current == current->parent->right) {
							left_turn(current);
							current = current->left;
						}
						if (current->parent->isblack)
							break;
						if (current->parent->parent) {
							current->parent->isblack = true;
							current->parent->parent->isblack = false;
							right_turn(current->parent);
						}
					}
				}
				else if (current->parent == current->parent->parent->right) {
					if (!current->parent->parent->left->isblack) {
						current->parent->parent->left->isblack = true;
						current->parent->parent->right->isblack = true;
						current->parent->parent->isblack = false;
						current = current->parent->parent;
					}
					else if (current->parent->left == current) {
						right_turn(current);
						current = current->left;
						current->isblack = true;
						current->parent->isblack = false;
						left_turn(current->parent);
					}
				}
			}
			else break;
		while (current->parent)
			current = current->parent;
		head = current;
		head->isblack = true;
	}
}

void Mymap::remove(int key) {
	Node* current = head, *remove;
	Node* currentforbalance = nullptr;
	bool isblackremove = false;
	count--;
	if(current) while (current->key != key && current != nill)
	{
		if (key > current->key) {
			current = current->right;
			continue;
		}
		else if (key < current->key) {
			current = current->left;
			continue;
		}
	}
	if (current) {
		if (current == nill)
			throw std::invalid_argument("Keys must be different!!");
	}
	else throw std::invalid_argument("Keys must be different!!");
	if (current != nill) {
		remove = current;
		isblackremove = remove->isblack;
		if (current->right == nill && current->left == nill) {
			if (current->parent) {
				current = current->parent;
				if (current->left == remove)
					current->left = nill;
				else
					current->right = nill;
				nill->parent = current;
				currentforbalance = nill;
				delete remove;
			}
			else {
				delete head;
				head = nullptr;
				current = head;
				isblackremove = false;
			}
		}
		else if (current->left == nill && current->right) {
			currentforbalance = current->right;
			if (current->parent) {
				current = current->parent;
				if (current->left == remove) {
					current->left = remove->right;
					current->left->parent = current;
				}
				else {
					current->right = remove->right;
					current->right->parent = current;
				}
				delete remove;
			}
			else {
				head = head->right;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->right == nill && current->left) {
			currentforbalance = current->left;
			if (current->parent) {
				current = current->parent;
				if (current->left == remove) {
					current->left = remove->left;
					current->left->parent = current;
				}
				else {
					current->right = remove->left;
					current->right->parent = current;
				}
				delete remove;
			}
			else {
				head = head->left;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->left != nill && current->right != nill && current->left && current->right) {
			current = current->right;
			while (current->left != nill)
				current = current->left;
			currentforbalance = current->right;
			isblackremove = current->isblack;
			if (current->parent == remove)
				currentforbalance->parent = current;
			else {
				current->parent->left = currentforbalance;
				if (currentforbalance->parent)
					currentforbalance->parent = current->parent;
			}
			if (remove->parent) {
				if (remove->parent->left == remove)
					remove->parent->left = current;
				else
					remove->parent->right == current;
			}
			current->left = remove->left;
			if (remove->left->parent != nill)
				remove->left->parent = current;
			if(current != remove->right)
				current->right = remove->right;
			current->parent = remove->parent;
			if (!remove->parent)
				head = current;
			current->isblack = isblackremove;
			delete remove;
		}
	}
	if(current == nill && head)
		throw std::invalid_argument("Keys must be different!!");
	if (isblackremove && head && currentforbalance) {
		while (currentforbalance->parent) {
			if (currentforbalance->parent->left == currentforbalance) {
				current = currentforbalance->parent->right;
				if (current) {
					if (!current->isblack) {
						current->isblack = true;
						current->parent->isblack = false;
						left_turn(current);
						current = currentforbalance->parent->right;
					}
					if(current->left && current->right) if (current->left->isblack == current->right->isblack && current->left->isblack) {
						current->isblack = false;
						currentforbalance = currentforbalance->parent;
					}
					else if (current->right->isblack) {
						current->left->isblack = true;
						current->isblack = false;
						right_turn(current->left);
						current = currentforbalance->parent->right;
					}
					else {
						current->isblack = currentforbalance->parent->isblack;
						currentforbalance->parent->isblack = true;
						current->right->isblack = true;
						left_turn(current);
					}
					while (current->parent)
						current = current->parent;
					head = current;
					currentforbalance = head;
				}
			}
			else {
				current = currentforbalance->parent->left;
				if (!current->isblack) {
					current->isblack = true;
					current->parent->isblack = false;
					right_turn(current);
					current = currentforbalance->parent->left;
				}
				if (current->left->isblack == current->right->isblack && current->left->isblack) {
					current->isblack = false;
					currentforbalance = currentforbalance->parent;
				}
				else if (current->right->isblack) {
					current->left->isblack = true;
					current->isblack = false;
					left_turn(current->left);
					current = currentforbalance->parent->right;
				}
				else {
					current->isblack = currentforbalance->parent->isblack;
					currentforbalance->parent->isblack = true;
					current->right->isblack = true;
					right_turn(current);
				}
				while (current->parent)
					current = current->parent;
				head = current;
				currentforbalance = head;
			}
			currentforbalance->isblack = true;
		}
	}
	if(nill) nill->parent = nullptr;
}

int Mymap::find(int key) {
	Node* current = head;
	while (current != nill) {
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else break;
	}
	if (current == nill)
		throw std::invalid_argument("lol");
	return current->value;
}

Listnum Mymap::get_keys() {
	return get_keys_or_value(true);
}

Listnum Mymap::get_values() {
	return get_keys_or_value(false);
}

void Mymap::clear() {
	while (head != nill)
		remove(head->key);
}

void Mymap::print() {
	Listnum listkeys, listvalues;
	listkeys = get_keys();
	listvalues = get_values();
	for (int i = 0; i < listkeys.get_size(); i++) {
		cout << "key: " << listkeys.get_elem(i) << "; value: " << listvalues.get_elem(i) << endl;
	}
}

void Mymap::left_turn(Node* swivel){
	Node* parent = swivel->parent;
	parent->right = swivel->left;
	if (swivel->left != nill) swivel->left->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent)
		head = swivel;
	else {
		if (parent == parent->parent->left)
			parent->parent->left = swivel;
		else
			parent->parent->right = swivel;
	}
	parent->parent = swivel;
	swivel->left = parent;
}

void Mymap::right_turn(Node* swivel) {
	Node* parent = swivel->parent;
	parent->left = swivel->right;
	if (swivel->right != nill) swivel->right->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent) 
		head = swivel;
	else {
		if (parent == parent->parent->right)
			parent->parent->right = swivel;
		else
			parent->parent->left = swivel;
	}
	parent->parent = swivel;
	swivel->right = parent;
}

Listnum Mymap::get_keys_or_value(bool iskeys) {
	if (head) {
		Listnum list;
		Node* current = head;
		while (count > list.get_size() && current) {
			while (current->left != nill && current->left) { // moves all the way to the left and adds elements
				if(iskeys) list.push_back(current->key);
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
		return list;
	}
	throw out_of_range("the tree does not exist!");
}
