#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/Mymap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestforlaba1 {
	TEST_CLASS(UnitTestforlaba1) {
	public:
		
		TEST_METHOD(Testinsert) {
			Mymap map;
			map.insert(1, 2);
			Assert::IsTrue(map.find(1) == 2);
			map.insert(2, 2);
			Assert::IsTrue(map.find(2) == 2);
			try {
				map.insert(2, 2);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "Keys must be different!!");
			}
		}
		TEST_METHOD(TestRemove) {
			int value = 50, key[] = {55,40,65,60,75,57};
			Mymap map;
			for (int i = 0; i < 6; i++) {
				map.insert(key[i], value);
			}
			map.remove(40);
			try {
				map.remove(40);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "key not found!!!");
			}
			map.remove(55);
			try {
				map.remove(55);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "key not found!!!");
			}
			map.remove(65);
			try {
				map.remove(65);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "key not found!!!");
			}
			map.remove(60);
			try {
				map.remove(60);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "key not found!!!");
			}
			map.remove(75);
			try {
				map.remove(75);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "key not found!!!");
			}
			map.remove(57);
			try {
				map.remove(57);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "array is empty!!!!");
			}
		}
		TEST_METHOD(TestFind) {
			Mymap map;
			map.insert(1, 2);
			Assert::IsTrue(map.find(1) == 2);
			try {
				map.find(500);
				Assert::IsTrue(false);
			}
			catch (const invalid_argument expection) {
				Assert::AreEqual(expection.what(), "Key not found!!");
			}
		}
		TEST_METHOD(TestGetList) {
			int value = 50, key[] = { 55,40,65,60,75,57 };
			Mymap map;
			Listnum maplist;
			try {
				maplist = map.get_keys();
				Assert::IsTrue(false);
			}
			catch (const out_of_range expection) {
				Assert::AreEqual(expection.what(), "the tree does not exist!");
			}
			for (int i = 0; i < 6; i++) {
				map.insert(key[i], value);
			}
			maplist = map.get_keys();
			Assert::IsTrue(maplist.contains(55) && maplist.contains(40) && maplist.contains(65)
				&& maplist.contains(60) && maplist.contains(75) && maplist.contains(57)
				&& maplist.get_size() == 6);
		}
	};
}
