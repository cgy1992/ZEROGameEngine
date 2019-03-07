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
using namespace ZERO::Graphics;

TextureNode::TextureNode()
	: SceneNode()
	, mpTexture(nullptr)
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
	case Texture::TextureType::DiffuseMap:
		mpTexture->BindPS();
		mpTexture->BindVS();
		break;
	case Texture::TextureType::SpecularMap:
		mpTexture->BindPS();
		break;
	case Texture::TextureType::DisplacementMap:
		mpTexture->BindVS();
		break;
	case Texture::TextureType::NormalMap:
		mpTexture->BindPS();
		break;
	}
}

void TextureNode::OnPostRender()
{
	switch (mpTexture->GetTextureType())
	{
	case Texture::TextureType::DiffuseMap:
		mpTexture->UnbindPS();
		mpTexture->UnbindVS();
		break;
	case Texture::TextureType::SpecularMap:
		mpTexture->UnbindPS();
		break;
	case Texture::TextureType::DisplacementMap:
		mpTexture->UnbindVS();
		break;
	}
}