#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class Listnum {
public:
    Listnum();
    ~Listnum();
    void push_back(int newnumber);
    void push_front(int newnumber);
    void pop_back();
    void pop_front();
    void insert(int newnumber, size_t index);
    bool contains(int number);
    int get_elem(size_t index);
    void remove(size_t index);
    size_t get_size();
    void clear();
    void set(size_t index, int newnumber);
    bool isEmpty();
    void push_front(Listnum newlist);
    void save_list();
    Listnum& operator=(Listnum Listnum);
    friend ostream& operator<< (ostream& out, const Listnum& list);
private:
    class Node {
    public:
        int number;
        class Node* next;
        Node(int newnumber = 0, Node* next = nullptr) {
            this->next = next;
            this->number= newnumber;
        }
        ~Node(){};
    };
    Node* head;
    size_t size;
    size_t savesize;
};