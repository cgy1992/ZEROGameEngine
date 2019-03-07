#ifndef INCLUDED_GRAPHICS_BONEANIMATION_H
#define INCLUDED_GRAPHICS_BONEANIMATION_H

#include "Animation.h"
#include "Bone.h"

namespace ZERO
{
namespace Graphics
{
	class BoneAnimation : public Animation
	{
	public:
		BoneAnimation();
		~BoneAnimation();

		int boneIndex;
	};

	typedef std::vector<BoneAnimation*> BoneAnimations;
}
}

#endif // !1
