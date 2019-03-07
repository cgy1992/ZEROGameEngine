
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MaterialNode.h"

using namespace ZERO;
using namespace ZERO::SCENE;
//====================================================================================================
// Class Definitions
//====================================================================================================

MaterialNode::MaterialNode()
	: SceneNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

MaterialNode::~MaterialNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::Initialize()
{
	mConstantBuffer.Initialize();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::OnRender()
{
	const Math::Vector4& ambient = mMaterial.ambient;
	const Math::Vector4& diffuse = mMaterial.diffuse;
	const Math::Vector4& specular = mMaterial.specular;
	const Math::Vector4& emissive = mMaterial.emissive;

	ConstantBuffer constants;
	constants.ambient = ambient;
	constants.diffuse = diffuse;
	constants.specular = specular;
	constants.emissive = emissive;
	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(3);
	mConstantBuffer.BindPS(3);
}