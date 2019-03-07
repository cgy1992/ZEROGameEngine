#ifndef INCLUDED_CORE_HANDLE_H
#define INCLUDED_CORE_HANDLE_H

namespace ZERO
{
namespace Core
{
	template<class DataType>
	class HandlePool;

	template <class DataType>
	class Handle
	{
	public:
		Handle();
		
		bool IsValid() const;
		void Invalidate();

		DataType* Get() const;
		DataType* operator->() const;

		bool operator==(Handle rhs) const { return mIndex == rhs.mIndex && mGeneration == rhs.mGeneration; }
		bool operator!=(Handle rhs) const { return !(*this == rhs); }


	private:
		friend HandlePool<DataType>;

		static HandlePool<DataType>* sPool;

		uint32_t mIndex : 24; //Bit Packing, specify the actual bits used in memory
		uint32_t mGeneration : 8; // but using it is like using a normal uint32_t
	};

	template<class DataType>
	HandlePool<DataType>* Handle<DataType>::sPool = nullptr;

	template<class DataType>
	Handle<DataType>::Handle()
		: mIndex(0)
		, mGeneration(0)
	{
	}

	template<class DataType>
	bool Handle<DataType>::IsValid() const
	{
		return sPool && sPool->IsValid(*this);
	}

	template<class DataType>
	void Handle<DataType>::Invalidate()
	{
		*this = Handle();
	}

	template<class DataType>
	DataType* Handle<DataType>::Get() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}

	template<class DataType>
	DataType* Handle<DataType>::operator->() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}
	

}//!namespace Core
}//!namespace ZERO





#endif // !INCLUDED_CORE_HANDLE_H
