
//====================================================================================================
// Includes
//====================================================================================================


#include "Precompiled.h"
#include "TransformNode.h"


//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

TransformNode::TransformNode(MatrixStack& ms)
	: SceneNode()
	, mMatrixStack(ms)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

TransformNode::~TransformNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::Initialize(uint32_t bindIndex)
{
	mConstantBuffer.Initialize();
	mBindIndex = bindIndex;
}

//----------------------------------------------------------------------------------------------------

void TransformNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPreRender()
{
	Math::Matrix4 world = mTransform.GetWorld();
	mMatrixStack.PushMatrix(world);
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnRender()
{
	ConstantBuffer constants;
	constants.matWorld = mMatrixStack.GetMatrixTranspose();
	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPostRender()
{
	mMatrixStack.PopMatrix();
}