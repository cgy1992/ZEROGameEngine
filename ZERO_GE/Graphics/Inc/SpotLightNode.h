#ifndef INCLUDED_GRAPHICS_SPOTLIGHTNODE_H
#define INCLUDED_GRAPHICS_SPOTLIGHTNODE_H


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
class SpotLightNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular;

		Math::Vector3 position;
		float range;

		Math::Vector3 direction;
		float spot;

		Math::Vector3 attenuation;
	};

	SpotLightNode();
	virtual ~SpotLightNode();

	void Initialize();
	void Terminate();

	SpotLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	SpotLight mLight;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // !INCLUDED_GRAPHICS_SPOTLIGHTNODE_H

