#ifndef INCLUDED_ENGINE_VERTEXSHADERRESOURCEMANAGER_H
#define INCLUDED_ENGINE_VERTEXSHADERRESOURCEMANAGER_H

#include "ResourceManager.h"

namespace ZERO
{
namespace Engine
{

class VertexShaderResourceManager : public ResourceManager<Graphics::VertexShader>
{

public:
	VertexShaderResourceManager();
	~VertexShaderResourceManager();

	std::string LoadResource(std::string path) override;
	void Terminate() override;
};

}
}

#endif // !INCLUDED_ENGINE_SHADERRESOURCEMANAGER_H

