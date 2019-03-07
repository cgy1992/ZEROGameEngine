#include "Precompiled.h"
#include "MetaField.h"

using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Core::Meta;

MetaField::MetaField(const char* const name, const MetaType* const type, size_t offset)
	: mName(name)
	, mType(type)
	, mOffset(offset)
{}
