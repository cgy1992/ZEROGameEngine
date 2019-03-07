#ifndef INCLUDED_ENGINE_MESHRESOURCEMANAGER_H
#define INCLUDED_ENGINE_MESHRESOURCEMANAGER_H

#include "ResourceManager.h"

namespace ZERO
{
namespace Engine
{
class PrimitiveMeshResourceManager : public ResourceManager<Graphics::Mesh>
{
public:
	PrimitiveMeshResourceManager();
	~PrimitiveMeshResourceManager();

	std::string LoadResource(std::string path) override;
	void Terminate() override;
};
}//!namespace Engine
}//!namespace ZERO






#endif // !INCLUDED_ENGINE_MESHRESOURCEMANAGER_H

