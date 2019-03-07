#include "Precompiled.h"
#include "TextureComponent.h"
#include "World.h"

using namespace ZERO;
using namespace ZERO::Engine;


META_DERIVED_BEGIN(TextureComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mTextureName, "Name")
		META_FIELD(mBindIndex, "BindIndex")
	META_FIELD_END
META_CLASS_END

TextureComponent::TextureComponent()
	: mTextureName("")
{
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Initialize()
{
	GetOwner().GetWorld().GetTextureManager()->GetResource(mTextureName)->SetBindIndex(mBindIndex);
}

void TextureComponent::Render()
{
	GetOwner().GetWorld().GetTextureManager()->GetResource(mTextureName)->BindVS();
	GetOwner().GetWorld().GetTextureManager()->GetResource(mTextureName)->BindPS();
}

void TextureComponent::Terminate()
{

}