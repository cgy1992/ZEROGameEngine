#ifndef INCLUDED_GRAPHICS_ANIMATIONCLIP_H
#define INCLUDED_GRAPHICS_ANIMATIONCLIP_H

#include "BoneAnimation.h"
#include "Model.h"

namespace ZERO
{
namespace Graphics
{
	class AnimationClip
	{
	public:
		AnimationClip();
		~AnimationClip();
		void GetTransform(float time, Bone* bone, Math::Matrix4& transform) const;

		void SerializeAnim();
		void DeserializeAnim(std::string animationName);

		BoneAnimations boneAnimations;
		std::string name;
		float duration;
		float ticksPerSecond;
		uint32_t totalNumberOfBones;
		uint32_t numberOfBonesWithAnim;

	};

	
}
}


#endif // !INCLUDED_GRAPHICS_ANIMATIONCLIP_H

