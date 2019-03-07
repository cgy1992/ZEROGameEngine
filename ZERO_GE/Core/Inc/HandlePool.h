#ifndef INCLUDED_CORE_HANDLEPOOL_H
#define INCLUDED_CORE_HANDLEPOOL_H

#include "Debug.h"
#include "Handle.h"

namespace ZERO
{
namespace Core
{

template<class DataType>
class HandlePool
{
public:
	using HandleType = Handle<DataType>;
	
	HandlePool(size_t capacity);
	~HandlePool();

	HandleType Register(DataType* instance);
	void Unregister(HandleType handle);

	bool IsValid(HandleType handle) const;
	DataType* Get(HandleType handle) const;


private:

	struct Entry
	{
		DataType* instance{ nullptr };
		uint32_t generation{ 0 };
	};

	std::vector<Entry> mEntries;
	std::vector<uint32_t> mFreeSlots;

};

template<class DataType>
HandlePool<DataType>::HandlePool(size_t capacity)
{
	ASSERT(capacity > 0, "[HandlePool] Invalid capacity.");

	mEntries.resize(capacity + 1);
	mFreeSlots.reserve(capacity);
	for (size_t i = capacity; i > 0; --i)
	{
		mFreeSlots.push_back(i);
	}

	ASSERT(HandleType::sPool == nullptr, "[HandlePool] Cannot have more than one pool for the same type.");
	HandleType::sPool = this;
}

template <class DataType>
HandlePool<DataType>::~HandlePool()
{
	ASSERT(mFreeSlots.size() == mFreeSlots.capacity(), "[HandlePool] There still registered slots!");

	ASSERT(HandleType::sPool == this, "[HandlePool] something is wrong");
	HandleType::sPool = nullptr;

}

template <class DataType>
Handle<DataType> HandlePool<DataType>::Register(DataType* instance)
{
	ASSERT(instance != nullptr, "[HandlePool] Invalid instance.");
	ASSERT(!mFreeSlots.empty(), "[HandlePool] No more free slots available.");

	uint32_t slot = mFreeSlots.back();
	mFreeSlots.pop_back();

	mEntries[slot].instance = instance;

	HandleType handle;
	handle.mIndex = slot;
	handle.mGeneration = mEntries[slot].generation;

	return handle;
}

template<class DataType>
void HandlePool<DataType>::Unregister(HandleType handle)
{
	if (!IsValid(handle))
	{
		return;
	}

	//Increments generation to invalidate all existing handles
	mEntries[handle.mIndex].generation++;

	//Recycle the slot
	mFreeSlots.push_back(handle.mIndex);
}

template<class DataType>
bool HandlePool<DataType>::IsValid(HandleType handle) const
{
	return handle != HandleType() && mEntries[handle.mIndex].generation == handle.mGeneration;
}

template<class DataType>
DataType* HandlePool<DataType>::Get(HandleType handle) const
{
	return IsValid(handle) ? mEntries[handle.mIndex].instance : nullptr;
}



}//!namespace Core
}//!namespace ZERO



#endif // INCLUDED_CORE_HANDLEPOOL_H
