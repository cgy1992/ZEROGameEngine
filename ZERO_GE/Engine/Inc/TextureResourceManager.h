#ifndef INCLUDED_ENGINE_TEXTURERESOURCEMANAGER_H
#define INCLUDED_ENGINE_TEXTURERESOURCEMANAGER_H

#include "ResourceManager.h"

namespace ZERO
{
namespace Engine
{
class TextureResourceManager : public ResourceManager<Graphics::Texture>
{

public:
	TextureResourceManager();
	~TextureResourceManager();

	std::string LoadResource(std::string path) override;
	void Terminate() override;
};
}//!namespace Engine
}//!namespace ZERO


#endif // !INCLUDED_ENGINE_TEXTURERESOURCEMANAGER_H

