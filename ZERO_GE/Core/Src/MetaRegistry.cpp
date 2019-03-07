#include "Precompiled.h"
#include "MetaRegistry.h"

#include "MetaClass.h"
#include "Debug.h"

using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Core::Meta;
using namespace ZERO::Core::Meta::MetaRegistry;


namespace
{
	using MetaClassMap = std::map<std::string, const MetaClass*>;
	MetaClassMap& GetRegistry()
	{
		static MetaClassMap sMetaClassMap;
		return sMetaClassMap;
	}
}

void ZERO::Core::Meta::MetaRegistry::Register(const MetaClass* metaClass)
{
	GetRegistry().emplace(metaClass->GetName(), metaClass);
}

const MetaClass* Core::Meta::MetaRegistry::FindMetaClass(const char* className)
{
	MetaClassMap::const_iterator iter = GetRegistry().find(className);
	ASSERT(iter != GetRegistry().end(), "[MetaRegistry] Meta class for %s not found.", className);
	return iter->second;
}