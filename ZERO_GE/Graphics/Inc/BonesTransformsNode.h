#ifndef INCLUDED_GRAPHICS_BONESTRANSFORMSNODE_H
#define INCLUDED_GRAPHICS_BONESTRANSFORMSNODE_H

#include "SceneNode.h"
#include "ConstantBuffer.h"

namespace ZERO
{
namespace Graphics
{
	class BonesTransformsNode : public SceneNode
	{
	public:
		struct ConstantBuffer
		{
			Math::Matrix4 bonesTransforms[100];
		};

		BonesTransformsNode();
		virtual ~BonesTransformsNode();

		void Initialize(uint32_t bindIndex = 0);
		void SetTransform(uint32_t index, const Math::Matrix4& transform) { mTransforms[index] = transform; }
		void Terminate();


	protected:
		virtual void OnRender();

	protected:
		TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

		std::vector<Math::Matrix4> mTransforms;
		uint32_t mBindIndex;
	};


}
}


#endif // !INCLUDED_GRAPHICS_BONESTRANSFORMSNODE_H

