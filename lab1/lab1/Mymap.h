#pragma once
#include <stdexcept>

class Mymap {
public:
	void insert(int key, int value);
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

	void left_turn(Node* swivel);
	void right_turn(Node* swivel);
};