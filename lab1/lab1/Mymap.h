#pragma once
#include <stdexcept>
#include "Listnum.h"

class Mymap {
public:
	~Mymap();
	void insert(int key, int value);
	void remove(int key);
	int find(int key);
	Listnum get_keys();
	Listnum get_values();
	void clear();
	void print();
private:
	class Node {
	public:
		int key;
		int value;
		bool isblack;
		Node* left;
		Node* right;
		Node* parent;
		Node(int newkey, int newvalue, bool newcolor = false, Node* newparent = nullptr, Node* newleft = nullptr, Node* newright = nullptr) {
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
	Node* nill = new Node(0, 0, true);
	void left_turn(Node* swivel);
	void right_turn(Node* swivel);
	Listnum get_keys_or_value(bool iskeys);
};