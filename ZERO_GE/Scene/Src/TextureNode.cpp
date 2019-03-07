//====================================================================================================
// Filename:	TextureNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "TextureNode.h"


//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::SCENE;

TextureNode::TextureNode()
	: SceneNode()
	, mpTexture(nullptr)
	, mIndex(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

TextureNode::~TextureNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void TextureNode::OnRender()
{
	switch (mpTexture->GetTextureType())
	{
	case Graphics::Texture::TextureType::DiffuseMap:
		mpTexture->BindPS(0);
		mpTexture->BindVS(0);
		break;
	case Graphics::Texture::TextureType::SpecularMap:
		mpTexture->BindPS(1);
		break;
	case Graphics::Texture::TextureType::DisplacementMap:
		mpTexture->BindVS(2);
		break;
	}
}