#include "Precompiled.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <Graphics/Inc/SimpleDraw.h>


using namespace ZERO;
using namespace ZERO::Engine;


META_DERIVED_BEGIN(ColliderComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mCenter, "Center")
		META_FIELD(mExtent, "Extend")
		META_FIELD(mColor, "Color")
	META_FIELD_END
META_CLASS_END

ColliderComponent::ColliderComponent()
	: mTransformComponent(nullptr)
	, mCenter(Math::Vector3::Zero())
	, mExtent(Math::Vector3::One())
	, mColor(Math::Vector4::Black())
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Initialize()
{
	mTransformComponent = (TransformComponent*)GetOwner().GetComponentAt(0);
}

void ColliderComponent::Render()
{
	Math::Vector3 center = mCenter + mTransformComponent->Position();
	Math::Vector3 min = center - mExtent;
	Math::Vector3 max = center + mExtent;
	Graphics::SimpleDraw::AddAABB(min, max, mColor);
}
