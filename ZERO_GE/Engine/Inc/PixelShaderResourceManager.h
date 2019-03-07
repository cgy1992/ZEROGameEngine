#ifndef INCLUDED_ENGINE_PIXELSHADERRESOURCEMANAGER_H
#define INCLUDED_ENGINE_PIXELSHADERRESOURCEMANAGER_H

#include "ResourceManager.h"

namespace ZERO
{
namespace Engine
{
class PixelShaderResourceManager : public ResourceManager<Graphics::PixelShader>
{
public:
	PixelShaderResourceManager();
	~PixelShaderResourceManager();

	std::string LoadResource(std::string path) override;
	void Terminate() override;

};
}//!namespace Engine
}//!namespace ZERO



#endif // !INCLUDED_ENGINE_PIXELSHADERRESOURCEMANAGER_H

