#ifndef INCLUDED_GRAPHICS_TRANSFORMNODE_H
#define INCLUDED_GRAPHICS_TRANSFORMNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "MatrixStack.h"
#include "Transform.h"
#include "ConstantBuffer.h"

namespace ZERO 
{
namespace Graphics
{
	//====================================================================================================
	// Class Declarations
	//====================================================================================================

class TransformNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Matrix4 matWorld;
	};

	TransformNode(MatrixStack& ms);
	virtual ~TransformNode();

	void Initialize(uint32_t bindIndex = 0);
	Transform& GetTransform() { return mTransform; }
	void Terminate();


protected:
	virtual void OnPreRender();
	virtual void OnRender();
	virtual void OnPostRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	MatrixStack& mMatrixStack;

	Transform mTransform;
	uint32_t mBindIndex;
};

}// !namespace Graphics
}// !namespace ZERO


#endif //!INCLUDED_GRAPHICS_TRANSFORMNODE_H