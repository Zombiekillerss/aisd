#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/Floyd.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab3
{
	TEST_CLASS(UnitTestlab3)
	{
	public:
		TEST_METHOD(ExeptionTest)
		{
			Floyd f;
			try 
			{
				f.cheapway("k", "l", "abrakadabra");
				Assert::IsTrue(false);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual("You entered the data incorrectly or the file was not found!!", e.what());
			}
		}
		TEST_METHOD(CorrectMatrixTest)
		{
			/*
			
			 old matrix
         	 col 1 2 3 4
		 row  1  0 8 0 1
		 row  2  0 0 1 0
		 row  3  4 0 0 0
		 row  4  0 2 9 0
			
			  matrix with short paths
			 col 1 2 3 4
		 row  1  0 3 4 1
		 row  2  5 0 1 6
		 row  3  4 7 0 5
		 row  4  7 2 3 0
			*/
			Floyd f;
			string str = f.cheapway("1", "2", "data.txt");
			Assert::AreEqual("1->4->2", str.c_str());
			str = f.cheapway("1", "3", "data.txt");
			Assert::AreEqual("1->4->2->3", str.c_str());
			str = f.cheapway("1", "4", "data.txt");
			Assert::AreEqual("1->4", str.c_str());
			str = f.cheapway("2", "1", "data.txt");
			Assert::AreEqual("2->3->1", str.c_str());
			str = f.cheapway("2", "3", "data.txt");
			Assert::AreEqual("2->3", str.c_str());
			str = f.cheapway("2", "4", "data.txt");
			Assert::AreEqual("2->3->1->4", str.c_str());
			str = f.cheapway("3", "1", "data.txt");
			Assert::AreEqual("3->1", str.c_str());
			str = f.cheapway("3", "2", "data.txt");
			Assert::AreEqual("3->1->4->2", str.c_str());
			str = f.cheapway("3", "4", "data.txt");
			Assert::AreEqual("3->1->4", str.c_str());
			str = f.cheapway("4", "1", "data.txt");
			Assert::AreEqual("4->2->3->1", str.c_str());
			str = f.cheapway("4", "2", "data.txt");
			Assert::AreEqual("4->2", str.c_str());
			str = f.cheapway("4", "3", "data.txt");
			Assert::AreEqual("4->2->3", str.c_str());
			str = f.cheapway("1", "1", "data.txt");
			Assert::AreEqual("1->1", str.c_str());
			str = f.cheapway("2", "2", "data.txt");
			Assert::AreEqual("2->2", str.c_str());
			str = f.cheapway("3", "3", "data.txt");
			Assert::AreEqual("3->3", str.c_str());
			str = f.cheapway("4", "4", "data.txt");
			Assert::AreEqual("4->4", str.c_str());
		}
	};
}
