
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "PointLightNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

PointLightNode::PointLightNode()
	: SceneNode()
{	// Empty
}

//----------------------------------------------------------------------------------------------------

PointLightNode::~PointLightNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void PointLightNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void PointLightNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void PointLightNode::OnRender()
{
	const Math::Vector4& ambient = mLight.ambient;
	const Math::Vector4& diffuse = mLight.diffuse;
	const Math::Vector4& specular = mLight.specular;

	const Math::Vector3& position = mLight.position;
	float range				= mLight.range;

	const Math::Vector3& attenuation = mLight.att;


	ConstantBuffer constants;
	constants.ambient =			ambient;
	constants.diffuse =			diffuse;
	constants.specular =		specular;
	constants.position =		position;
	constants.range =			range;
	constants.attenuation =		attenuation;

	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(5);
	mConstantBuffer.BindPS(5);
}