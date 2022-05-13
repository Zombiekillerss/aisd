#include "pch.h"
#include "CppUnitTest.h"
#include "../kyr/Fulkerson.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestkyr1
{
	TEST_CLASS(UnitTestkyr1)
	{
	public:
		
		TEST_METHOD(ExpectionTest)
		{
			try
			{
				Fulkerson f;
				int sum = f.maxflow("abracadabra");
				Assert::IsTrue(false);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual("You entered the data incorrectly or the file was not found!!", e.what());
			}
		}
		TEST_METHOD(ExamplesTest)
		{
			/*
			* lecture example
			*/
			Fulkerson f;
			int sum = 0, expected = 3;
			sum = f.maxflow("example1.txt");
			Assert::AreEqual(expected, sum);
			expected = 10;
			/*
			 example from here https://habr.com/ru/post/566248/ 
				in 2 variations: when rows and columns are in one position and another
			*/
			sum = f.maxflow("example2.txt");
			Assert::AreEqual(expected, sum);
			sum = f.maxflow("example3.txt");
			Assert::AreEqual(expected, sum);
		}
	};
}
