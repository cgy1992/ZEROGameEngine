
//====================================================================================================
// Includes
//====================================================================================================


#include "Precompiled.h"
#include "MaterialNode.h"

using namespace ZERO;
using namespace ZERO::Graphics;
//====================================================================================================
// Class Definitions
//====================================================================================================

MaterialNode::MaterialNode()
	: SceneNode()
{}

//----------------------------------------------------------------------------------------------------

MaterialNode::~MaterialNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::Initialize(uint32_t bindIndex)
{
	mConstantBuffer.Initialize();
	mBindIndex = bindIndex;
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
	const float power = mMaterial.power;
	const int hasDiffuse = mMaterial.hasDiffuseMap;
	const int hasSpecular = mMaterial.hasSpecularMap;
	const int hasNormal = mMaterial.hasNormalMap;
	const int hasDisplacement = mMaterial.hasDisplacementMap;

	ConstantBuffer constants;
	constants.ambient = ambient;
	constants.diffuse = diffuse;
	constants.specular = specular;
	constants.emissive = emissive;
	constants.power = power;
	constants.hasDiffuseMap = hasDiffuse;
	constants.hasSpecularMap = hasSpecular;
	constants.hasNormalMap = hasNormal;
	constants.hasDisplacementMap = hasDisplacement;

	mConstantBuffer.Set(constants);
	
	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}