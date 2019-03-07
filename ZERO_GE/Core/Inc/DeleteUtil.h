//==============================================================================
//Filename: DeleteUtil.h
//Created By: Erick Tavares
//==============================================================================


#ifndef INCLUDED_CORE_DELETEUTIL_H
#define INCLUDED_CORE_DELETEUTIL_H

#include "Common.h"

template <class T>
inline void SafeDelete(T*& ptr)
{
	delete ptr;
	ptr = nullptr;
}

template<class T>
inline void SafeDeleteArray(T*& ptr)
{
	delete[] ptr;
	ptr = nullptr;
}

template<class T>
inline void SafeRelease(T*& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}

template<class T>
inline void SafeDeleteVec(std::vector<T*>& vec)
{
	for (uint32_t i = 0; i < vec.size(); ++i)
	{
		SafeDelete(&vec[i]);
	}
}

#endif // #ifndef INCLUDED_CORE_DELETEUTIL_H
