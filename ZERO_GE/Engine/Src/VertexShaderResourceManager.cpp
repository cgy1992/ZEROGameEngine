#include "Precompiled.h"
#include "VertexShaderResourceManager.h"


using namespace ZERO;
using namespace ZERO::Engine;

VertexShaderResourceManager::VertexShaderResourceManager()
{}

VertexShaderResourceManager::~VertexShaderResourceManager()
{}

std::string VertexShaderResourceManager::LoadResource(std::string path)
{
	std::unique_ptr<Graphics::VertexShader> vShader = std::make_unique<Graphics::VertexShader>();

	//Converting to const wchar_t*-------------------------------------------------------
	std::wstring wideStringVS = std::wstring(path.begin(), path.end());
	const wchar_t* wideCStrVS = wideStringVS.c_str();
	//-----------------------------------------------------------------------------------

	//Getting the name of the resource--------------------------------------------------
	std::size_t found = path.find_last_of("/\\");
	std::size_t found2 = path.find_last_of(".");
	std::string fileName = path.substr(found + 1, (found2-1)-found);
	//---------------------------------------------------------------------------------

	//Initializing Shaders----------------------
	vShader->Initialize(wideCStrVS, "VS", "vs_5_0", Graphics::Vertex::Format);

	mResources.try_emplace(fileName, std::move(vShader));

	return fileName;
}

void VertexShaderResourceManager::Terminate()
{
	for (auto& resource : mResources)
	{
		resource.second->Terminate();
	}
}