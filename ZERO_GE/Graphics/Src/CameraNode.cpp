

//====================================================================================================
// Includes
//====================================================================================================
#include "Precompiled.h"
#include "CameraNode.h"


using namespace ZERO;
using namespace ZERO::Graphics;
//====================================================================================================
// Class Definitions
//====================================================================================================

CameraNode::CameraNode()
	: SceneNode()
	, mCameras({})
	, mBindIndex(1)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CameraNode::~CameraNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Initialize(uint32_t bindIndex)
{
	mConstantBuffer.Initialize();
	mBindIndex = bindIndex;
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::OnRender()
{
	ConstantBuffer constants;

	constants.matView		[0]	= Math::Transpose(mCameras[0]->GetView());
	constants.matProjection [0] = Math::Transpose(mCameras[0]->GetProjection());
	constants.viewPosition	[0] = { mCameras[0]->GetPosition(), 1.0f};
	constants.cameraNear	[0] = mCameras[0]->GetNearPlane();
	constants.cameraFar		[0] = mCameras[0]->GetFarPlane();

	constants.matView		[1] = Math::Transpose(mCameras[1]->GetView());
	constants.matProjection [1] = Math::Transpose(mCameras[1]->GetProjection());
	constants.viewPosition	[1] = { mCameras[1]->GetPosition(), 1.0f };
	constants.cameraNear	[1] = mCameras[1]->GetNearPlane();
	constants.cameraFar		[1] = mCameras[1]->GetFarPlane();

	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}