#include "MyBitArr.h"

MyBitArr::~MyBitArr() 
{
	boolArr.~MyList();
}

MyBitArr::MyBitArr(const MyBitArr& bitarr)
{
	boolArr = bitarr.boolArr;
}

void MyBitArr::addNewBit(bool newBit) 
{
	boolArr.push_back(newBit);
}

std::string MyBitArr::tostring()
{
	std::string str;
	for (int i = 0; i < boolArr.get_size(); i++)
	{
		if (boolArr.get_elem(i))
			str += "1";
		else
			str += "0";
	}
	return str;
}

void MyBitArr::deletbitend()
{
	boolArr.pop_back();
}

void MyBitArr::clear()
{
	boolArr.clear();
}

bool MyBitArr::operator==(MyBitArr arr1) 
{
	if (boolArr.get_size() != arr1.boolArr.get_size())
		return false;
	for (rsize_t i = 0; i < boolArr.get_size(); i++)
		if (boolArr.get_elem(i) != arr1.boolArr.get_elem(i))
			return false;
	return boolArr.get_size() > 0;
}
