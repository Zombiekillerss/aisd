#include "Mymap.h"

void Mymap::insert(int newkey, int newvalue) {
	Node* current = head;
	if (!head)
		head = new Node(newkey, newvalue, true);
	else {
		while (true) if (newkey > current->key) {
			if (current->right)
				current = current->right;
			else {
				current->right = new Node(newkey, newvalue);
				current->right->parent = current;
				current = current->right;
				break;
			}
		}
		else if (newkey != current->key) {
			if (current->left)
				current = current->left;
			else {
				current->left = new Node(newkey, newvalue);
				current->left->parent = current;
				current = current->left;
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

void Mymap::left_turn(Node* swivel){
	Node* parent = swivel->parent;
	if (swivel->left)
		parent->right = swivel->left;
	swivel->parent = parent->parent;
	if (!parent->parent)
		parent->parent = swivel;
	else {
		if (parent == parent->parent->left)
			parent->parent->left = swivel;
		else
			parent->parent->right = swivel;
		parent->parent = swivel;
	}
	swivel->left = parent;
}

void Mymap::right_turn(Node* swivel) {
	Node* parent = swivel->parent;
	if (swivel->right)
		parent->left = swivel->right;
	swivel->parent = parent->parent;
	if (!parent->parent) 
		parent->parent = swivel;
	else {
		if (parent == parent->parent->right)
			parent->parent->right = swivel;
		else
			parent->parent->left = swivel;
		parent->parent = swivel;
	}
	swivel->right = parent;
}
