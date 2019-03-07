#include "Precompiled.h"
#include "PrimitiveMeshResourceManager.h"

using namespace ZERO;
using namespace ZERO::Engine;

PrimitiveMeshResourceManager::PrimitiveMeshResourceManager()
{}

PrimitiveMeshResourceManager::~PrimitiveMeshResourceManager()
{}

std::string PrimitiveMeshResourceManager::LoadResource(std::string path)
{
	std::unique_ptr<Graphics::Mesh> cubeMesh= std::make_unique<Graphics::Mesh>();
	std::unique_ptr<Graphics::Mesh> sphereMesh = std::make_unique<Graphics::Mesh>();
	std::unique_ptr<Graphics::Mesh> planeMesh = std::make_unique<Graphics::Mesh>();
	std::unique_ptr<Graphics::Mesh> skySphereMesh = std::make_unique<Graphics::Mesh>();
	std::unique_ptr<Graphics::Mesh> cylinderMesh = std::make_unique<Graphics::Mesh>();
	std::unique_ptr<Graphics::Mesh> coneMesh = std::make_unique<Graphics::Mesh>();

	Graphics::MeshBuilder::CreateCube(*cubeMesh.get());
	Graphics::MeshBuilder::CreateSphere(*sphereMesh.get(), 40, 40);
	Graphics::MeshBuilder::CreatePlane(*planeMesh.get());
	Graphics::MeshBuilder::CreateSkySphere(*skySphereMesh.get(), 100, 100);
	Graphics::MeshBuilder::CreateCylinder(*cylinderMesh.get(), 40, 40);
	Graphics::MeshBuilder::CreateCustomCylinder(*coneMesh.get(), 1.0f, 0.0f, 1.0f, 40, 40);

	mResources.try_emplace("Cube", std::move(cubeMesh));
	mResources.try_emplace("Sphere", std::move(sphereMesh));
	mResources.try_emplace("Plane", std::move(planeMesh));
	mResources.try_emplace("SkySphere", std::move(skySphereMesh));
	mResources.try_emplace("Cylinder", std::move(cylinderMesh));
	mResources.try_emplace("Cone", std::move(coneMesh));

	return "SUCCESSFULL";
}

void PrimitiveMeshResourceManager::Terminate()
{
	for (auto& resource : mResources)
	{
		resource.second->Destroy();
	}
}