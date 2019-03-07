#ifndef INCLUDED_GRAPHICS_BONE_H
#define INCLUDED_GRAPHICS_BONE_H

namespace ZERO
{
namespace Graphics
{
	struct Bone
	{
		Bone();
		~Bone();

		std::string name;

		Bone* parent;
		std::vector<Bone*> children;

		int index; 
		int parentIndex; 
		std::vector<uint32_t> childrenIndex;

		Math::Matrix4 transform;
		Math::Matrix4 offsetTransform;
	};
}// !namespace Graphics
}// !namespace ZERO



#endif // !INCLUDED_GRAPHICS_BONE_H

