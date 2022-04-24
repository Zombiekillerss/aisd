#pragma once
#include "MyList.h"

class MyBitArr {
public:
	MyBitArr() {};
	~MyBitArr();
	MyBitArr(const MyBitArr&);
	void addNewBit(bool);
	void deletbitend();
	void clear();
	bool operator== (MyBitArr);
private:
	MyList<bool> boolArr;
};

