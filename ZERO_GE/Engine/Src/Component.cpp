#include "Precompiled.h"
#include "Component.h"

using namespace ZERO;
using namespace ZERO::Engine;

META_CLASS_BEGIN(Component)
	META_NO_FIELD
META_CLASS_END

Component::Component()
	: mGameObject{ nullptr }
{
}

Component::~Component()
{
}
