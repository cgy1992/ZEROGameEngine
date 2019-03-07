#ifndef INCLUDED_CORE_TYPEDALLOCATOR_H
#define INCLUDED_CORE_TYPEDALLOCATOR_H

#include "BlockAllocator.h"

namespace ZERO
{
namespace Core
{
	template<class T>
	class TypedAllocator : private BlockAllocator
	{
	public:

		TypedAllocator(uint32_t capacity) 
			: BlockAllocator(sizeof(T), capacity)
		{}

		~TypedAllocator()
		{}

	


		template<class... Args>
		T* New(Args&&... args)
		{
			T* chunk = static_cast<T*>(Allocate());

			if (chunk)
			{
				new(chunk) T(std::forward<Args>(args)...);
			}

			return chunk;
		}

		void Delete(T* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}
			ptr->~T();
			Free(ptr);
		}
	};
}//! namespace Core
}//! namespace ZERO






#endif // !INCLUDED_CORE_TYPEDALLOCATOR_H

