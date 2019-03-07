#include "Precompiled.h"
#include "MetaArray.h"


using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Core::Meta;

MetaArray::MetaArray(const char* const name,
				size_t size,
				ZERO::Core::Meta::MetaType::CreateFunc create,
				ZERO::Core::Meta::MetaType::DestroyFunc destroy,
				size_t numOfElements)
	: MetaType{ name, Category::Array, size, std::move(create), std::move(destroy) }
	, mNumElements(numOfElements)
{}
