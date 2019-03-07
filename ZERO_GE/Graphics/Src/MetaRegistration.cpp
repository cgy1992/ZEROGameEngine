#include "Precompiled.h"
#include "MetaRegistration.h"


void ZERO::Graphics::Meta::MetaRegister()
{
#define REGISTER(x) ZERO::Core::Meta::MetaRegistry::Register(x::StaticGetMetaClass())
	

	//REGISTER();
	//REGISTER();

#undef Register
}

META_TYPE_DEFINE(ZERO::Graphics::Meta::Int4, "Int4")

