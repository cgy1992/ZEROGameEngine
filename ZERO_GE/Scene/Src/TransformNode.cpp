//====================================================================================================
// Filename:	TransformNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "TransformNode.h"



//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::SCENE;

TransformNode::TransformNode(Graphics::MatrixStack& ms)
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

void TransformNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnUpdate(float deltaTime)
{
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPreRender()
{
	mMatrixStack.PushMatrix(mTransform.GetTransform());
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnRender()
{
	ConstantBuffer constants;
	constants.matWorld = mMatrixStack.GetMatrixTranspose();
	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(0);
	mConstantBuffer.BindPS(0);
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPostRender()
{
	mMatrixStack.PopMatrix();
}