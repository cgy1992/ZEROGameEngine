
//====================================================================================================
// Includes
//====================================================================================================
#include "Precompiled.h"

#include "SceneManager.h"




using namespace ZERO;
using namespace ZERO::Graphics;
//====================================================================================================
// Class Definitions
//====================================================================================================

SceneManager::SceneManager(Graphics::MatrixStack& ms)
	: mMatrixStack(ms)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SceneManager::~SceneManager()
{
}

//----------------------------------------------------------------------------------------------------

CameraNode* SceneManager::CreateCameraNode()
{
	CameraNode* newNode = new CameraNode();
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

CameraNode* SceneManager::CreateCameraNode(uint32_t index)
{
	CameraNode* newNode = new CameraNode();
	newNode->Initialize(index);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

DepthMapNode* SceneManager::CreateDepthMapNode(uint32_t index)
{
	DepthMapNode* newNode = new DepthMapNode();
	newNode->Initialize(index);
	mNodes.push_back(newNode);
	return newNode;
}


InputNode* SceneManager::CreateInputNode()
{
	InputNode* newNode = new InputNode();
	mNodes.push_back(newNode);
	return newNode;
}

DirectionalLightNode* SceneManager::CreateDirectionalLightNode()
{
	DirectionalLightNode* newNode = new DirectionalLightNode();
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}
//----------------------------------------------------------------------------------------------------

PointLightNode* SceneManager::CreatePointLightNode()
{
	PointLightNode* newNode = new PointLightNode();
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}
//----------------------------------------------------------------------------------------------------

SpotLightNode* SceneManager::CreateSpotLightNode()
{
	SpotLightNode* newNode = new SpotLightNode();
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}
//----------------------------------------------------------------------------------------------------

MaterialNode* SceneManager::CreateMaterialNode()
{
	MaterialNode* newNode = new MaterialNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

MeshNode* SceneManager::CreateMeshNode()
{
	MeshNode* newNode = new MeshNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

SamplerNode* SceneManager::CreateSamplerNode(Sampler::Filter filter, Sampler::AddressMode address)
{
	SamplerNode* newNode = new SamplerNode();
	newNode->Initialize(filter, address);
	mNodes.push_back(newNode);
	return newNode;
}


SamplerNode* SceneManager::CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address, uint32_t index)
{
	SamplerNode* newNode = new SamplerNode();
	newNode->Initialize(filter, address, index);
	mNodes.push_back(newNode);
	return newNode;
}
//----------------------------------------------------------------------------------------------------

ShaderNode* SceneManager::CreateShaderNode()
{
	ShaderNode* newNode = new ShaderNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TextureNode* SceneManager::CreateTextureNode()
{
	TextureNode* newNode = new TextureNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TransformNode* SceneManager::CreateTransformNode(uint32_t bindIndex)
{
	TransformNode* newNode = new TransformNode(mMatrixStack);
	newNode->Initialize(bindIndex);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

RasterizerStateNode* SceneManager::CreateRasterizerStateNode()
{
	RasterizerStateNode* newNode = new RasterizerStateNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------

RenderTargetNode* SceneManager::CreateRenderTargetNode(uint32_t index)
{
	RenderTargetNode* newNode = new RenderTargetNode();
	newNode->Initialize(index);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

BonesTransformsNode* SceneManager::CreateBonesTransformsNode()
{
	BonesTransformsNode* newNode = new BonesTransformsNode();
	mNodes.push_back(newNode);
	return newNode;
}

void SceneManager::Purge()
{
	for (auto node : mNodes)
	{
		SafeDelete(node);
	}
	mNodes.clear();
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Update(float deltaTime)
{
	mRoot.Update(deltaTime);
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Render()
{
	mRoot.Render();
}