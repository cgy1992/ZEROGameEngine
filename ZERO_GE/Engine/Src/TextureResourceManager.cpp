#include "Precompiled.h"
#include "TextureResourceManager.h"

using namespace ZERO;
using namespace ZERO::Engine;

TextureResourceManager::TextureResourceManager()
	:ResourceManager()
{}

TextureResourceManager::~TextureResourceManager()
{}

std::string TextureResourceManager::LoadResource(std::string path)
{
	std::unique_ptr<Graphics::Texture> texture = std::make_unique<Graphics::Texture>();
	texture->Initialize(path.c_str());
	std::size_t found = path.find_last_of("/\\");
	std::size_t found2 = path.find_last_of(".");
	std::string fileName = path.substr(found + 1, (found2 - 1) - found);

	
	mResources.try_emplace(fileName, std::move(texture));

	return fileName;
}

void TextureResourceManager::Terminate()
{
	for (auto& resource : mResources)
	{
		resource.second->Terminate();
	}
}