#ifndef INCLUDED_GRAPHICS_POINTLIGHTNODE_H
#define INCLUDED_GRAPHICS_POINTLIGHTNODE_H


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
class PointLightNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular;

		Math::Vector3 position;

		float range;

		Math::Vector3 attenuation;
	};

	PointLightNode();
	virtual ~PointLightNode();

	void Initialize();
	void Terminate();

	PointLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	PointLight mLight;
};
}// !namespace Graphics
}// !namespace ZERO


#endif // !INCLUDED_GRAPHICS_POINTLIGHTNODE_H
