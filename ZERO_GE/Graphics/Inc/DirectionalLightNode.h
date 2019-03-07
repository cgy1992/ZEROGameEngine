#ifndef INCLUDED_GRAPHICS_DIRECTLIGHTNODE_H
#define INCLUDED_GRAPHICS_DIRECTLIGHTNODE_H


//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "Light.h"
#include "ConstantBuffer.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
namespace ZERO
{
namespace Graphics
{
class DirectionalLightNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular;
		Math::Vector3 direction;
	};

	DirectionalLightNode();
	virtual ~DirectionalLightNode();

	void Initialize();
	void Terminate();

	DirectionalLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	DirectionalLight mLight;
};
}// !namespace Graphics
}// !namespace ZERO


#endif //!INCLUDED_GRAPHICS_DIRECTLIGHTNODE_H