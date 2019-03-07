
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "SceneManager.h"
#include "CameraNode.h"
#include "DirectionalLightNode.h"
#include "PointLightNode.h"
#include "SpotLightNode.h"
#include "MaterialNode.h"
#include "MeshNode.h"
#include "SamplerNode.h"
#include "ShaderNode.h"
#include "TextureNode.h"
#include "TransformNode.h"


using namespace ZERO;
using namespace ZERO::SCENE;
//====================================================================================================
// Class Definitions
//====================================================================================================

SceneManager::SceneManager(Graphics::MatrixStack& ms)
	: mMatrixStack(ms)
	, mpRoot(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SceneManager::~SceneManager()
{
	ASSERT(mNodes.empty(), "[SceneManager] Purge() must be called before destruction.");
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
	newNode->Initialize();
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

SamplerNode* SceneManager::CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address)
{
	SamplerNode* newNode = new SamplerNode();
	newNode->Initialize(filter, address);
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

TransformNode* SceneManager::CreateTransformNode()
{
	TransformNode* newNode = new TransformNode(mMatrixStack);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::SetRoot(SceneNode* root)
{
	mpRoot = root;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Purge()
{
	const uint32_t numNodes = mNodes.size();
	for (uint32_t i = 0; i < numNodes; ++i)
	{
		SafeDelete(mNodes[i]);
	}
	mNodes.clear();
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Update(float deltaTime)
{
	if (mpRoot != nullptr)
	{
		mpRoot->Update(deltaTime);
	}
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Render()
{
	if (mpRoot != nullptr)
	{
		mpRoot->Render();
	}
}