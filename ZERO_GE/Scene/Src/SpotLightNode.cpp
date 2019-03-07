
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SpotLightNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::SCENE;

SpotLightNode::SpotLightNode()
	: SceneNode()
{	// Empty
}

//----------------------------------------------------------------------------------------------------

SpotLightNode::~SpotLightNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void SpotLightNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void SpotLightNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void SpotLightNode::OnRender()
{
	const Math::Vector4& ambient =		mLight.ambient;
	const Math::Vector4& diffuse =		mLight.diffuse;
	const Math::Vector4& specular =		mLight.specular;

	const Math::Vector3& position =		mLight.position;
	const float& range =				mLight.range;

	Math::Vector3& direction =			mLight.direction;
	float& spot =						mLight.spot;

	const Math::Vector3& attenuation =	mLight.att;


	ConstantBuffer constants;
	constants.ambient =			ambient;
	constants.diffuse =			diffuse;
	constants.specular =		specular;

	constants.position =		position;
	constants.range =			range;

	constants.direction =		direction;
	constants.spot =			spot;

	constants.attenuation =		attenuation;

	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(2);
	mConstantBuffer.BindPS(2); 
}
