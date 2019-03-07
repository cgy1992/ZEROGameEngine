#include "Precompiled.h"
#include "MetaType.h"

using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Core::Meta;

MetaType::MetaType(const char* const name, Category category, size_t size, CreateFunc create,
	DestroyFunc destroy)
	: mName(name)
	, mCategory(category)
	, mID(std::hash_value(name)) //mId(std::hash<string>()(name)
	, mSize(size)
	, mCreate(std::move(create))
	, mDestroy(std::move(destroy))
{}