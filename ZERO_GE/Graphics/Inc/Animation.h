#ifndef INCLUDED_GRAPHICS_ANIMATION_H
#define INCLUDED_GRAPHICS_ANIMATION_H

#include "Keyframe.h"
#include "Transform.h"

namespace ZERO
{
namespace Graphics
{

	class Animation
	{
	public:
		Animation();
		~Animation();

		Math::Matrix4 GetTransform(float time);

		void AddPositionKey	(Keyframe<Math::Vector3> pos);
		std::vector<Keyframe<Math::Vector3>>& GetPositionKeys() { return mPositionKeyframes; }

		void AddRotationKey	(Keyframe<Math::Quaternion> rot);
		std::vector<Keyframe<Math::Quaternion>>& GetRotationKeys() { return mRotationKeyframes; }

		void AddScaleKey	(Keyframe<Math::Vector3> scale);
		std::vector<Keyframe<Math::Vector3>>& GetScaleKeys() { return mScaleKeyframes; }

		void Reset() { currentPositionIndex = 0; currentRotationIndex = 0; currentScaleIndex = 0; }

		void SetLoop(bool loop) { mLoop = loop; }
		void SortFrames();

	private:
		uint32_t								currentPositionIndex{ 0 };
		uint32_t								currentScaleIndex{ 0 };
		uint32_t								currentRotationIndex{ 0 };

		std::vector<Keyframe<Math::Vector3>>	mPositionKeyframes;
		std::vector<Keyframe<Math::Quaternion>>	mRotationKeyframes;
		std::vector<Keyframe<Math::Vector3>>	mScaleKeyframes;
		bool									mLoop;

		template<typename T>
		bool isKeyVector3Set(float time, std::vector<Keyframe<T>> vec);

	};
}// !namespace Graphics
}// !namespace ZERO

#endif // !INCLUDED_GRAPHICS_ANIMATION_H


