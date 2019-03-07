#ifndef INCLUDED_SCENE_POINTLIGHTNODE_H
#define INCLUDED_SCENE_POINTLIGHTNODE_H


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

	Graphics::PointLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::PointLight mLight;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SCENE_POINTLIGHTNODE_H
