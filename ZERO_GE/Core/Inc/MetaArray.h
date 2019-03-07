#ifndef INCLUDED_CORE_METAARRAY
#define INCLUDED_CORE_METAARRAY

#include "MetaType.h"

namespace ZERO
{
namespace Core
{
namespace Meta
{

class MetaArray : public MetaType
{
public:
	MetaArray(	const char* const name,
				size_t size,
				ZERO::Core::Meta::MetaType::CreateFunc create,
				ZERO::Core::Meta::MetaType::DestroyFunc destroy,
				size_t numOfElements);

	size_t GetNumOfElements() const { return mNumElements; }

private:
	size_t mNumElements;
	
	

};
}//!namespace Meta
}//!namespace Core
}//!namespace ZERO



#endif // !INCLUDED_CORE_METAARRAY

