#ifndef INCLUDED_CORE_META_METAREGISTRY
#define INCLUDED_CORE_META_METAREGISTRY


namespace ZERO
{
namespace Core
{
namespace Meta
{
class MetaClass;
namespace MetaRegistry
{
	void Register(const MetaClass* metaClass);
	const MetaClass* FindMetaClass(const char* className);
}//!namespace Core
}//!namespace Meta
}//!namespace MetaRegistry

}




#endif // !INCLUDED_CORE_META_METAREGISTRY

