#ifndef INCLUDED_SCENE_SPOTLIGHTNODE_H
#define INCLUDED_SCENE_SPOTLIGHTNODE_H


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

	Graphics::SpotLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::SpotLight mLight;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SCENE_SPOTLIGHTNODE_H

