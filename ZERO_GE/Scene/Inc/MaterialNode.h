#ifndef INCLUDED_SCENE_MATERIALNODE_H
#define INCLUDED_SCENE_MATERIALNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include <Graphics/Inc/Graphics.h>
#include "SceneNode.h"

//====================================================================================================
// Class Declarations
//====================================================================================================


namespace ZERO
{
namespace SCENE
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
	};

	MaterialNode();
	virtual ~MaterialNode();

	void Initialize();
	void Terminate();

	Graphics::Material& GetMaterial() { return mMaterial; }

protected:
	virtual void OnRender();

protected:
	Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::Material mMaterial;
};
} //!namespace SCENE
} //!namespace ZERO 


#endif // #ifndef INCLUDED_SIEGE_TRANSFORMNODE_H