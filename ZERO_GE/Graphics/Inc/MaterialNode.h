#ifndef INCLUDED_GRAPHICS_MATERIALNODE_H
#define INCLUDED_GRAPHICS_MATERIALNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "Material.h"
#include "ConstantBuffer.h"
//====================================================================================================
// Class Declarations
//====================================================================================================


namespace ZERO
{
namespace Graphics
{
class MaterialNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular; //w - will be the specular power
		Math::Vector4 emissive;
		float power;
		int hasDiffuseMap;
		int hasSpecularMap;
		int hasNormalMap;
		int hasDisplacementMap;
	};

	MaterialNode();
	virtual ~MaterialNode();

	void Initialize(uint32_t bindIndex = 3);
	void Terminate();

	Material& GetMaterial() { return mMaterial; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Material mMaterial;
	uint32_t mBindIndex;
};
} //!namespace SCENE
} //!namespace ZERO 


#endif //!INCLUDED_GRAPHICS_MATERIALNODE_H