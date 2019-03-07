#ifndef INCLUDED_CORE_META_H
#define INCLUDED_CORE_META_H

#include "MetaUtil.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaType.h"

#define META_TYPE_DECLARE(Type)\
	template <> const ZERO::Core::Meta::MetaType* ZERO::Core::Meta::GetMetaType<Type>();

#define META_TYPE_DEFINE(Type, Name)\
	template <> const ZERO::Core::Meta::MetaType* ZERO::Core::Meta::GetMetaType<Type>()\
	{\
		static ZERO::Core::Meta::MetaType sMetaType(\
			Name,\
			ZERO::Core::Meta::MetaType::Category::Primitive,\
			sizeof(Type),\
			[]{return new Type;},\
			[](void* data){delete static_cast<Type*>(data);}\
			);\
		return &sMetaType;\
	}

#define META_CLASS_DECLARE\
	static const ZERO::Core::Meta::MetaClass* StaticGetMetaClass();\
	virtual const ZERO::Core::Meta::MetaClass* GetMetaClass() const { return StaticGetMetaClass(); }

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	template <> const ZERO::Core::Meta::MetaType* ZERO::Core::Meta::GetMetaType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const ZERO::Core::Meta::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using Class = ClassType;\
		const char* const className = #ClassType;

#define META_DERIVED_BEGIN(ClassType, ParentType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const ZERO::Core::Meta::MetaClass* parentMetaClass = ParentType::StaticGetMetaClass();

#define META_CLASS_BEGIN(ClassType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const ZERO::Core::Meta::MetaClass* parentMetaClass = nullptr;

#define META_FIELD_BEGIN\
		static const ZERO::Core::Meta::MetaField fields[] = {

#define META_FIELD(Var, Name)\
		ZERO::Core::Meta::MetaField(Name, ZERO::Core::Meta::GetMetaType(&Class::Var), ZERO::Core::Meta::GetFieldOffset(&Class::Var)),

#define META_FIELD_END\
		};\
		static const size_t numFields = std::size(fields);

#define META_NO_FIELD\
		static const ZERO::Core::Meta::MetaField* fields = nullptr;\
		static const uint32_t numFields = 0;

#define META_CLASS_END\
		static const ZERO::Core::Meta::MetaClass sMetaClass(className, sizeof(Class),\
		[] {return new Class(); },\
		[](void* data)	{delete static_cast<Class*>(data);},\
		parentMetaClass, fields, numFields);\
		return &sMetaClass;\
	}

#define META_ARRAY_DECLARE(Type)\
	const ZERO::Core::Meta::MetaArray* GetMetaArray();

#define META_ARRAY_DEFINE(Type, name, numberOfElements)\
	const ZERO::Core::Meta::MetaArray* GetMetaArray()\
	{\
		static const ZERO::Core::Meta::MetaArray sMetaArray(name, sizeof(Type) * numberOfElements, \
		[] {return new Type[numberOfElements]; }, \
		[](void* data) {delete static_cast<Type*>(data); }, \
		numberOfElements);\
		return &sMetaArray;\
	}

META_TYPE_DECLARE(int)
META_TYPE_DECLARE(float)
META_TYPE_DECLARE(bool)
META_TYPE_DECLARE(std::string)


#endif // !INCLUDED_CORE_META_H
