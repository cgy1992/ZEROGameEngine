#ifndef INCLUDED_GRAPHICS_ANIMATIONBUILDER_H
#define INCLUDED_GRAPHICS_ANIMATIONBUILDER_H

#include "Animation.h"

namespace ZERO
{
namespace Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder();
		~AnimationBuilder();

		AnimationBuilder& SetTime(float time) { mTime = time; }
		AnimationBuilder& AddPositionKey(Math::Vector3 position, float time);
		AnimationBuilder& AddRotationKey(Math::Quaternion rotation, float time);
		AnimationBuilder& AddScaleKey(Math::Vector3 scale, float time);
		AnimationBuilder& SetInitialState(const Transform& transform);
		AnimationBuilder& Loop(bool loopState);
		AnimationBuilder& Build();

		Animation& GetAnimation() { return mAnimation; }

	private:
		Animation mAnimation;
		float mTime;
	};
}// !namespace Graphics
}// !namespace ZERO

#endif // !INCLUDED_GRAPHICS_ANIMATIONBUILDER_H


