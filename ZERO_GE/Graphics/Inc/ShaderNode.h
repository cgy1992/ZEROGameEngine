#ifndef INCLUDED_GRAPHICS_SHADERNODE_H
#define INCLUDED_GRAPHICS_SHADERNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "VertexShader.h"
#include "PixelShader.h"

namespace ZERO
{
namespace Graphics
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class ShaderNode : public SceneNode
{
public:
	ShaderNode();
	virtual ~ShaderNode();

	void SetVertexShader(VertexShader* vertexShader) { mpVertexShader = vertexShader; }
	void SetPixelShader(PixelShader* pixelShader) { mpPixelShader = pixelShader; }

protected:
	virtual void OnRender();

protected:
	VertexShader*	mpVertexShader;
	PixelShader*	mpPixelShader;
};
}// !namespace Graphics
}// !namespace ZERO


#endif //!INCLUDED_GRAPHICS_SHADERNODE_H