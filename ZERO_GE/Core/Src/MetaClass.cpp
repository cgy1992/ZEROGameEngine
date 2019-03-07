#include "Precompiled.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaRegistry.h"
#include "Debug.h"

using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Core::Meta;


MetaClass::MetaClass(	const char* const name, 
						size_t size,
						ZERO::Core::Meta::MetaType::CreateFunc create,
						ZERO::Core::Meta::MetaType::DestroyFunc destroy,
						const MetaClass* const parent,
						const MetaField* const fields, 
						size_t numFields)
	: MetaType	(name, MetaType::Category::Class, size, std::move(create), std::move(destroy))
	, mParent	(parent)
	, mFields	(fields)
	, mNumFields(numFields)
{}

const MetaClass* MetaClass::GetParent() const
{
	return mParent;
}
const MetaField* MetaClass::FindField(const char* name) const
{
	const MetaField* field = nullptr;

	for (size_t i = 0; i < mNumFields; ++i)
	{
		const MetaField& f = mFields[i];
		if (std::strcmp(f.GetName(), name) == 0)
		{
			field = &f;
			break;
		}
	}


	//If the field is not found, try the parent
	if (field == nullptr && mParent != nullptr)
	{
		field = mParent->FindField(name);
	}

	return field;
}

void MetaClass::Dump() const
{
	LOG("Class[%s]", GetName())
	for (size_t i = 0; i < mNumFields; ++i)
	{
		auto& field = mFields[i];
		LOG("has field [%s] of type [%s] and offset of [%zd]", field.GetName(), field.GetMetaType()->GetName(), field.GetOffset());

	}
	if (mParent)
	{
		LOG("is derived from [%s]", mParent->GetName());
	}
}
