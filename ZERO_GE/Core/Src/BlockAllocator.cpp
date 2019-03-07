#include "Precompiled.h"
#include "BlockAllocator.h"

#include "Debug.h"


//(4 + 2) 2 = 12 


using namespace ZERO::Core;

BlockAllocator::BlockAllocator(uint32_t blocksize, uint32_t capacity) 
	: mBlockSize(blocksize)
	, mCapacity(capacity)
	, mFreeSlotIndex(0)
{
	ASSERT((blocksize != 0) || (capacity != 0), "[Memory]Blocksize can't be zero.");
	mData = (uint8_t*)malloc(blocksize * capacity);

	for (uint32_t i = 0; i < capacity; ++i)
	{
		uint32_t index = i * blocksize;

		int8_t keyValue = static_cast<int8_t>((i + 1));

		if ((keyValue * blocksize) >= (blocksize * capacity))
		{
			keyValue = -1;
		}

		int8_t* memoryKey = (int8_t*)&mData[index];
		*memoryKey = keyValue;
		memoryKey = nullptr;
	}
}

BlockAllocator::~BlockAllocator()
{
	free(mData);
	mFreeSlots.clear();
}

void* BlockAllocator::Allocate()
{
	if (mFreeSlotIndex != -1)
	{
		uint32_t memIndex = static_cast<uint32_t>((mFreeSlotIndex * mBlockSize));

		void* memoryBlock = &mData[memIndex];

		int8_t* newKey = (int8_t*)&mData[static_cast<uint32_t>(memIndex)];

		mFreeSlotIndex = *newKey;

		newKey = nullptr;

		return memoryBlock;
	}
	return nullptr;
}

void BlockAllocator::Free(void* ptr)
{
	uint8_t* ptrUInt = (uint8_t*)ptr;

	size_t distance = (ptrUInt - mData);
	
	ASSERT(distance > 0 || distance < ((mBlockSize * mCapacity) - mBlockSize), "[Memory] Distance should be inside the memory range.");

	int8_t temp = mFreeSlotIndex;

	int8_t* newKey = (int8_t*)&mData[static_cast<uint32_t>(distance)];

	mFreeSlotIndex = *newKey;

	*newKey = temp;

	newKey = nullptr;
}