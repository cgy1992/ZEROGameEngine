
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "DirectionalLightNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

DirectionalLightNode::DirectionalLightNode()
	: SceneNode()
{	// Empty
}

//----------------------------------------------------------------------------------------------------

DirectionalLightNode::~DirectionalLightNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void DirectionalLightNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void DirectionalLightNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void DirectionalLightNode::OnRender()
{
	const Math::Vector4& ambient =		mLight.ambient;
	const Math::Vector4& diffuse =		mLight.diffuse;
	const Math::Vector4& specular =		mLight.specular;
	const Math::Vector3& direction =	mLight.direction;

	ConstantBuffer constants;
	constants.ambient = ambient;
	constants.diffuse = diffuse;
	constants.specular = specular;
	constants.direction = direction;
	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(2); //TO Be Defined
	mConstantBuffer.BindPS(2); //To Be Defined
}