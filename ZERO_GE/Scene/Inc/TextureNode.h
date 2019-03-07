#ifndef INCLUDED_SIEGE_TEXTURENODE_H
#define INCLUDED_SIEGE_TEXTURENODE_H

//====================================================================================================
// Filename:	TextureNode.h
// Created by:	Peter Chan
// Description:	Class for a texture node.
//====================================================================================================

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

class TextureNode : public SceneNode
{
public:
	TextureNode();
	virtual ~TextureNode();

	void SetTexture(Graphics::Texture* texture) { mpTexture = texture; }
	Graphics::Texture* GetTexture() const { return mpTexture; }

	void SetIndex(uint32_t index) { mIndex = index; }
	uint32_t GetIndex() const { return mIndex; }

protected:
	virtual void OnRender();

protected:
	Graphics::Texture * mpTexture;
	uint32_t mIndex;
};
}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SIEGE_TEXTURENODE_H