#ifndef INCLUDED_GRAPHICS_TEXTURENODE_H
#define INCLUDED_GRAPHICS_TEXTURENODE_H


//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "Texture.h"

namespace ZERO
{
namespace Graphics
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class TextureNode : public SceneNode
{
public:
	TextureNode();
	virtual ~TextureNode();

	void SetTexture(Texture* texture) { mpTexture = texture; }
	Texture* GetTexture() const { return mpTexture; }


protected:
	virtual void OnRender();
	virtual void OnPostRender();

protected:
	Texture* mpTexture;
};
}// !namespace Graphics
}// !namespace ZERO


#endif //!INCLUDED_GRAPHICS_TEXTURENODE_H