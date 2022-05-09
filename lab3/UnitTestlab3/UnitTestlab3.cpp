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
	};
}
