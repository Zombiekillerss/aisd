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
		TEST_METHOD(Test)
		{
			Fulkerson f;
			int sum = 0;
			sum = f.maxflow("example1.txt");
			std::cout << endl << "Maximum flow: " << sum << endl;
			sum = f.maxflow("example2.txt");
			std::cout << endl << "Maximum flow: " << sum << endl;
			sum = f.maxflow("example3.txt");
		}
	};
}
