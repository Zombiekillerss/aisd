#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;


template<typename T>
class MyList 
{
public:
    MyList();
    ~MyList();
    int find(T value);
    void push_back(T newvalue);
    void push_front(T newvalue);
    void pop_back();
    void pop_front();
    void insert(T newvalue, int index);
    bool contains(T value);
    T get_elem(int index);
    void remove(int index);
    void removeel(T);
    int get_size();
    void clear();
    void set(int index, T newvalue);
    bool isEmpty();
    void push_front(MyList newlist);
    MyList& operator=(MyList MyList);
    MyList(const MyList&);
    friend ostream& operator<< (ostream& out, const MyList& list);
private:
    class Node 
    {
    public:
        T value;
        class Node* next;
        Node(T newvalue = 0, Node* next = nullptr) 
        {
            this->next = next;
            this->value = newvalue;
        }
        ~Node(){};
    };
    Node* head;
    Node* end;
    int size;
};

template<typename T>
MyList<T>::MyList() 
{
    size = 0;
    head = nullptr;
    end = nullptr;
}

template<typename T>
MyList<T>::~MyList() 
{
    clear();
}

template<typename T>
inline int MyList<T>::find(T value)
{
    Node* current = head;
    for (int i = 0; i < size; i++) {
        if (current->value == value)
            return i;
        current = current->next;
    }
    return -1;
}

template<typename T>
void MyList<T>::push_back(T newvalue) 
{
    if (!head)
    {
        head = new Node(newvalue); // creates a list with newnumber
        end = head;
    }
    else {
        end->next = new Node(newvalue);
        end = end->next;
    }
    size++;
}

template<typename T>
void MyList<T>::push_front(T newvalue) 
{
    if (!head)
    {
        head = new Node(newvalue); // creates a list with newnumber
        end = head;
    }
    else {
        Node* first = new Node(newvalue); // creates a list with newnumber
        first->next = head; // the next elements of the list are equal to the elements of the old list
        head = first; // the list is updated
    }
    size++;
}

template<typename T>
void MyList<T>::pop_back() 
{
    if (head) 
    {
        Node* current = head, * previous = nullptr;
        while (current->next)
        {
            previous = current; // keeps the last element of the list
            current = current->next; // moves the current list while the next item exists
        }
        delete current; // clears memory 
        current = nullptr;
        end = previous;
        if (previous) previous->next = current; // updates the pointer
        else head = nullptr;
        size--;
    }
}

template<typename T>
void MyList<T>::pop_front() 
{
    if (head) 
    {
        Node* current = head->next;
        delete head;
        head = current;
        size--;
        if (!head)
            end = head;
    }
}

template<typename T>
void MyList<T>::insert(T newvalue, int index) 
{
    if (size >= index + 1)
    {
        Node* current = head;
        if (!index) 
            push_front(newvalue); // if index = 0 then add newnumber to the beginning
        else if (index + 1 == size) 
            push_back(newvalue);
        else
        {
            for (int i = 1; i < index; i++, current = current->next); // move the current list item to index
            Node* newelem = new Node(newvalue);  // creates a list with newnumber
            newelem->next = current->next; // insert the list item before index element
            current->next = newelem;
            size++;
        }
    }
}

template<typename T>
bool MyList<T>::contains(T value) 
{
    Node* current = head;
    while (current) {
        if (current->value == value)
            return true;
        current = current->next;
    }
    return false;
}

template<typename T>
T MyList<T>::get_elem(int index)
{
    if (size >= index + 1) 
    {
        Node* current = head;
        for (int i = 0; i < index; i++, current = current->next); // moves the current list to index inclusive
        return current->value; // returns index number
    }
    else
        throw out_of_range("index is entered incorrectly"); // error message
}

template<typename T>
void MyList<T>::remove(int index)
{
    if (size >= index + 1) 
    {
        if (index == 0) pop_front(); // delete first element
        else if (index + 1 == size) pop_back(); // delete last element
        else 
        {
            Node* current = head, * next;
            for (int i = 1; i < index - 1; i++, current = current->next);  // moves the current list to index
            next = current->next;
            current->next = next->next;
            delete next;
            next = nullptr;
            size--;
        }
    }
}

template<typename T>
inline void MyList<T>::removeel(T elem)
{
    if (size && contains(elem))
    {
        if (head->value == elem) pop_front();
        else
        {
            Node* current = head, * next;
            while (current->value != elem)
                if (current->next->value == elem)
                    break;
                else current = current->next;
            next = current->next;
            current->next = next->next;
            delete next;
            next = nullptr;
            size--;
        }
    }
}

template<typename T>
int MyList<T>::get_size()
{
    return size;
}

template<typename T>
void MyList<T>::clear() 
{
    while (size && head)
        pop_front();
}

template<typename T>
void MyList<T>::set(int index, T newvalue)
{
    if (size >= index + 1) 
    {
        Node* current = head;
        for (int i = 0; i < index; i++, current = current->next); // moves the current list to index inclusive
        current->value = newvalue;
    }
}

template<typename T>
bool MyList<T>::isEmpty() 
{
    return head == nullptr;
}

template<typename T>
ostream& operator<< (ostream& out, const MyList<T>& list) 
{
    MyList<T> current;
    current.head = list.head;
    while (current.head) {
        out << current.head->number;
        if (current.head->next) out << ',';
        current.head = current.head->next;
    }
    current.size = 0;  // since size = 0 the destructor will not delete the memory
    return out;
}

template<typename T>
void MyList<T>::push_front(MyList<T> newlist) 
{
    if (newlist.head) 
    {
        Node* current = newlist.head;
        while (current) 
        {
            push_front(current->value);
            current = current->next;
        }
        current = head;
        while (current) 
        {
            push_back(current->value);
            current = current->next;
        }
        newlist.head = nullptr;
    }
}

template<typename T>
MyList<T>& MyList<T>::operator=(MyList<T> list) 
{
    this->head = list.head;
    list.head = nullptr;
    end = list.end;
    this->size = list.size;
    return *this;
}

template<typename T>
inline MyList<T>::MyList(const MyList& list)
{
    Node* current = list.head;
    head = nullptr;
    end = nullptr;
    size = 0;
    while (current)
    {
        push_back(current->value);
        current = current->next;
    }
}
