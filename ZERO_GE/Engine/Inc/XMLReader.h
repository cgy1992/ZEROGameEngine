#ifndef INCLUDED_ENGINE_XMLREADER_H
#define INCLUDED_ENGINE_XMLREADER_H

#include <TinyXml/Inc/tinyxml2.h>

using namespace tinyxml2;

namespace ZERO
{
namespace Engine
{
namespace XMLReader
{
	bool Read(void* component, const Core::Meta::MetaClass* metaclass, const XMLNode* data);
	void* TypeReader(const char* typeName, const char* value, size_t& sizeOfType);
}//!namespace XMLREADER
}//!namespace Engine
}//!namespace ZERO

#endif // !INCLUDED_ENGINE_XMLREADER_H

