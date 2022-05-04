#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2/HuffmanTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab2
{
	TEST_CLASS(UnitTestlab2)
	{
	public:
		
		TEST_METHOD(TestCodeOneSymbol)
		{
			HuffmanT huf;
			std::string str = "t";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "0 ";
			Assert::AreEqual(str, huf.getcodestr());
		}
		TEST_METHOD(TestCodeTwoSymbols)
		{
			HuffmanT huf;
			std::string str = "to";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "0 1 ";
			Assert::AreEqual(str, huf.getcodestr());
		}
		TEST_METHOD(TestCodeThreeSymbols)
		{
			HuffmanT huf;
			std::string str = "asd";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "11 0 10 ";
			Assert::AreEqual(str, huf.getcodestr());
		}
		TEST_METHOD(TestString)
		{
			HuffmanT huf;
			std::string str = "it is test string";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "110 01 111 110 00 111 01 1011 00 01 111 00 01 1001 110 1000 1010 ";
			Assert::AreEqual(str, huf.getcodestr());
		}
		TEST_METHOD(TestStrings)
		{
			HuffmanT huf;
			std::string str = "it is test string";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "110 01 111 110 00 111 01 1011 00 01 111 00 01 1001 110 1000 1010 ";
			Assert::AreEqual(str, huf.getcodestr());
			str = "The joys of this life are not its joys";
			std::cout << endl;
			huf.encoding(str);
			Assert::AreEqual(huf.getdecodestr(), str);
			str = "10001 11101 1011 00 0100 1111 1001 011 00 1111 0101 00 1100 11101 1101 011 00 10101 1101 0101 1011 00 10000 11100 1011 00 10100 1111 1100 00 1101 1100 011 00 0100 1111 1001 011 ";
			Assert::AreEqual(str, huf.getcodestr());
		}
		TEST_METHOD(TestEmptyException)
		{
			HuffmanT huf;
			std::string str = "";
			std::cout << endl;
			try
			{
				huf.encoding(str);
				Assert::IsTrue(false);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "The string cannot be empty!!");
			}
			
		}
	};
}
