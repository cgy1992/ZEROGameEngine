#ifndef INCLUDED_CORE_METACLASS
#define INCLUDED_CORE_METACLASS

#include "MetaType.h"

namespace ZERO
{
namespace Core
{
namespace Meta
{
class MetaField;

class MetaClass : public MetaType
{
public:
	MetaClass(	const char* const name, 
				size_t size,
				ZERO::Core::Meta::MetaType::CreateFunc create,
				ZERO::Core::Meta::MetaType::DestroyFunc destroy,
				const MetaClass* const parent,
				const MetaField* const fields, 
				size_t numFields);

	const MetaClass* GetParent() const;
	const MetaField* FindField(const char* name) const;

	void Dump() const;

private:

	const MetaClass* const mParent{ nullptr };
	const MetaField* const mFields{ nullptr };
	const size_t mNumFields{ 0 };
	

};
}//!namespace Meta
}//!namespace Core
}//!namespace ZERO



#endif // !INCLUDED_CORE_METACLASS
