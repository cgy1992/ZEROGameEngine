#ifndef INCLUDED_SCENE_DIRECTLIGHTNODE_H
#define INCLUDED_SCENE_DIRECTLIGHTNODE_H


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

	Graphics::DirectionalLight& GetLight() { return mLight; }

protected:
	virtual void OnRender();

protected:
	Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::DirectionalLight mLight;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SCENE_DIRECTLIGHTNODE_H