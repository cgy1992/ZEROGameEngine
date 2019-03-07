#ifndef INCLUDED_ENGINE_COLLIDERCOMPONENT_H
#define INCLUDED_ENGINE_COLLIDERCOMPONENT_H

#include "Component.h"

namespace ZERO
{
namespace Engine
{
class TransformComponent;

class ColliderComponent : public Component
{
public:
	META_CLASS_DECLARE
	ColliderComponent();
	~ColliderComponent() override;

	void Initialize() override;
	void Render() override;

	void SetCenter(const Math::Vector3& center) { mCenter = center; }
	void SetExtent(const Math::Vector3& extent) { mExtent = extent; }
	void SetColor(const Math::Vector4& color)	{ mColor = color; }

	Math::Vector3 GetCenter	()	const	{ return mCenter; }
	Math::Vector3 GetExtent	()	const	{ return mExtent; }
	Math::Vector4 GetColor	()	const	{ return mColor;  }

private:
	Math::Vector3 mCenter;
	Math::Vector3 mExtent;
	Math::Vector4 mColor;
	const TransformComponent* mTransformComponent;
};
}//!namespace Engine
}//!namespace ZERO


#endif // !INCLUDED_ENGINE_COLLIDERCOMPONENT_H

