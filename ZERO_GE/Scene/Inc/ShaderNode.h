#ifndef INCLUDED_SIEGE_SHADERNODE_H
#define INCLUDED_SIEGE_SHADERNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include <Graphics/Inc/Graphics.h>
#include "SceneNode.h"

namespace ZERO
{
namespace SCENE
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class ShaderNode : public SceneNode
{
public:
	ShaderNode();
	virtual ~ShaderNode();

	void SetVertexShader(Graphics::VertexShader* vertexShader) { mpVertexShader = vertexShader; }
	void SetPixelShader(Graphics::PixelShader* pixelShader) { mpPixelShader = pixelShader; }

protected:
	virtual void OnRender();

protected:
	Graphics::VertexShader *	mpVertexShader;
	Graphics::PixelShader*		mpPixelShader;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SIEGE_SHADERNODE_H