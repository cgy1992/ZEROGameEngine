//====================================================================================================
// Filename:	CameraNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "CameraNode.h"

using namespace ZERO;
using namespace ZERO::SCENE;
//====================================================================================================
// Class Definitions
//====================================================================================================

CameraNode::CameraNode()
	: SceneNode()
	, mpCamera(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CameraNode::~CameraNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::OnUpdate(float deltaTime)
{
}

//----------------------------------------------------------------------------------------------------

void CameraNode::OnRender()
{
	ConstantBuffer constants;
	constants.matView = Math::Transpose(mpCamera->GetView());
	constants.matProjection = Math::Transpose(mpCamera->GetProjection());
	constants.viewPosition = mpCamera->GetPosition();
	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(1);
	mConstantBuffer.BindPS(1);
}