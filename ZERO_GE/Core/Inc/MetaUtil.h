#ifndef INCLUDED_CORE_METAUTIL_H
#define INCLUDED_CORE_METAUTIL_H


namespace ZERO
{
namespace Core
{
namespace Meta
{

class MetaType;
class MetaArray;

template<class DataType>
inline const MetaType* GetMetaType()
{
	static_assert(sizeof(DataType) == -1, "Cannot deduce type");
}

template<class ClassType, class T>
inline const MetaType* GetMetaType(T ClassType::*)
{
	return GetMetaType<T>();
}


template <class ClassType, class DataType>
inline size_t GetFieldOffset(DataType ClassType::* field)
{
	return(size_t)(void*)&(((ClassType*)nullptr)->*field);
}


template<class BaseType, class DerivedType>
DerivedType* DynamicCast(BaseType* ptr)
{
	if (ptr->GetMetaClass() != DerivedType::StaticGetMetaClass())
	{
		return nullptr;
	}
	return static_cast<DerivedType*>(ptr);
}

template<class BaseType, class DerivedType>
inline bool IsBaseOf(BaseType* base, DerivedType* derived)
{
	auto parent = derived->StaticGetMetaClass()->GetParent();
	while (parent)
	{
		if (parent == base->StaticGetMetaClass()->Get)
		{
			return true;
		}
		parent = parent->GetParent();
	}

	return false;
}

}
}
}


#endif // !INCLUDED_CORE_METAUTIL_H

