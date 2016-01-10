#include "stdafx.h"
#include "CppUnitTest.h"
#include "Unit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace vessTest
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(testGetHP)
		{
			Unit unit;
			Assert::AreEqual(100, unit.getHP());
		}

	};
}