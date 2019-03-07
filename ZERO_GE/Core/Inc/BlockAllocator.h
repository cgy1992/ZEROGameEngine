#ifndef INCLUDED_CORE_BLOCKALLOCATOR_H
#define INCLUDED_CORE_BLOCKALLOCATOR_H


namespace ZERO
{
namespace Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(uint32_t blocksize, uint32_t capacity);
		~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;

		void* Allocate();
		void Free(void* ptr);

	protected:
		uint8_t* mData;
		uint32_t mBlockSize;
		uint32_t mCapacity;
		std::vector<uint32_t> mFreeSlots;

		int8_t mFreeSlotIndex;

	};
}//!namespace Core
}//!namespace ZERO


//TODO: Try to implement the block mData, 2 x uint32_t, one integer to hold the key.


#endif // !INCLUDED_CORE_BLOCKALLOCATOR_H

