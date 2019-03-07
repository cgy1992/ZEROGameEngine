#include "Precompiled.h"
#include "MetaRegistration.h"

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "MeshRendererComponent.h"



void ZERO::Engine::Meta::MetaRegister()
{
#define REGISTER(x) ZERO::Core::Meta::MetaRegistry::Register(x::StaticGetMetaClass())

	REGISTER(ColliderComponent);
	REGISTER(TransformComponent);
	REGISTER(TextureComponent);
	REGISTER(MeshRendererComponent);
	REGISTER(CameraComponent);

#undef Register
}
