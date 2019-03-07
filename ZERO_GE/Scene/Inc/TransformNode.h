#ifndef INCLUDED_SIEGE_TRANSFORMNODE_H
#define INCLUDED_SIEGE_TRANSFORMNODE_H

//====================================================================================================
// Filename:	TransformNode.h
// Created by:	Peter Chan
// Description:	Class for a transform node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================
#include <Graphics/Inc/Graphics.h>
#include "SceneNode.h"

namespace ZERO 
{
namespace SCENE
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

	TransformNode(Graphics::MatrixStack& ms);
	virtual ~TransformNode();

	void Initialize();
	Graphics::Transform& GetTransform() { return mTransform; }
	void Terminate();

	//Transform& GetTransform() { return mTransform; }

protected:
	virtual void OnUpdate(float deltaTime);
	virtual void OnPreRender();
	virtual void OnRender();
	virtual void OnPostRender();

protected:
	Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::MatrixStack& mMatrixStack;

	Graphics::Transform mTransform;
};

}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SIEGE_TRANSFORMNODE_H