#include "Precompiled.h"
#include "PixelShaderResourceManager.h"


using namespace ZERO;
using namespace ZERO::Engine;

PixelShaderResourceManager::PixelShaderResourceManager()
{}

PixelShaderResourceManager::~PixelShaderResourceManager()
{}

std::string PixelShaderResourceManager::LoadResource(std::string path)
{
	std::unique_ptr<Graphics::PixelShader> pShader = std::make_unique<Graphics::PixelShader>();

	//Converting to const wchar_t*-------------------------------------------------------
	std::wstring wideStringPS = std::wstring(path.begin(), path.end());
	const wchar_t* wideCStrPS = wideStringPS.c_str();
	//-----------------------------------------------------------------------------------

	//Getting the name of the resource--------------------------------------------------
	std::size_t found = path.find_last_of("/\\");
	std::size_t found2 = path.find_last_of(".");
	std::string fileName = path.substr(found + 1, (found2 - 1) - found);
	//---------------------------------------------------------------------------------

	//Initializing Shaders----------------------
	pShader->Initialize(wideCStrPS);

	mResources.try_emplace(fileName, std::move(pShader));

	return fileName;
}

void PixelShaderResourceManager::Terminate()
{
	for (auto& pshader : mResources)
	{
		pshader.second->Terminate();
	}
}