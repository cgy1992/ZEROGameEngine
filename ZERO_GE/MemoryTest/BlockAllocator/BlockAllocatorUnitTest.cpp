#include "stdafx.h"
#include "CppUnitTest.h"
#include <Core/Inc/Core.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ZERO::Core;


namespace BlockAllocatorUTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AllocateFunction)
		{
			BlockAllocator ba{ 4, 2 };
			uint32_t* data = nullptr;

			data = (uint32_t*)ba.Allocate();
			
			uint32_t myTestNumber = 4;
			data = &myTestNumber;
			Assert::IsNotNull(data);

		}

		TEST_METHOD(AllocateTwiceFunction)
		{
			BlockAllocator ba{ 4, 2 };
			uint32_t* data = nullptr;
			uint32_t* data2 = nullptr;

			data = (uint32_t*)ba.Allocate();
			data2 = (uint32_t*)ba.Allocate();


			uint32_t myTestNumber = 4;
			uint32_t myTestNumber2 = 10;
			data = &myTestNumber;
			data2 = &myTestNumber2;
			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);

		}

		TEST_METHOD(Allocate_3_Variables)
		{
			BlockAllocator ba{ 4, 2 };
			uint32_t* data = nullptr;
			uint32_t* data2 = nullptr;
			uint32_t* data3 = nullptr;

			data = (uint32_t*)ba.Allocate();
			data2 = (uint32_t*)ba.Allocate();
			data3 = (uint32_t*)ba.Allocate();


			uint32_t myTestNumber = 4;
			uint32_t myTestNumber2 = 10;
			

			data = &myTestNumber;
			data2 = &myTestNumber2;
	

			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
			Assert::IsNull(data3);

		}

		TEST_METHOD(FreeUnitTest)
		{
			BlockAllocator ba{ 4, 3 };
			uint32_t* data = nullptr;
			uint32_t* data2 = nullptr;
			uint32_t* data3 = nullptr;
			char* data4 = nullptr;
			char* data5 = nullptr;
			char* data6 = nullptr;

			data = (uint32_t*)ba.Allocate();
			data2 = (uint32_t*)ba.Allocate();
			data3 = (uint32_t*)ba.Allocate();


			uint32_t myTestNumber = 4;
			uint32_t myTestNumber2 = 10;
			uint32_t myTestNumber3 = 20;

			*data = myTestNumber;
			*data2 = myTestNumber2;
			*data3 = myTestNumber3;

			ba.Free(data3);
			ba.Free(data);

			data4 = (char*)ba.Allocate();
			*data4 = 'a';

			data5 = (char*)ba.Allocate();
			*data5 = 'e';

			data6 = (char*)ba.Allocate();
	
			Assert::IsNull(data3);
			Assert::IsNull(data);

		}
	};
}