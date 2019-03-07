#ifndef INCLUDED_GRAPHICS_SCENEMANAGER_H
#define INCLUDED_GRAPHICS_SCENEMANAGER_H

#include "BonesTransformsNode.h"
#include "CameraNode.h"
#include "DepthMapNode.h"
#include "DirectionalLightNode.h"
#include "InputNode.h"
#include "PointLightNode.h"
#include "SpotLightNode.h"
#include "MaterialNode.h"
#include "MatrixStack.h"
#include "MeshNode.h"
#include "RasterizerStateNode.h"
#include "RenderTargetNode.h"
#include "Sampler.h"
#include "SamplerNode.h"
#include "ShaderNode.h"
#include "TextureNode.h"
#include "TransformNode.h"

namespace ZERO
{
namespace Graphics
{
	//====================================================================================================
	// Class Declarations
	//====================================================================================================

	class SceneManager
	{
	public:
		SceneManager(Graphics::MatrixStack& ms);
		~SceneManager();

		CameraNode* CreateCameraNode();
		CameraNode* CreateCameraNode(uint32_t index);
		DepthMapNode* CreateDepthMapNode(uint32_t index);
		DirectionalLightNode* CreateDirectionalLightNode();
		InputNode* CreateInputNode();
		PointLightNode* CreatePointLightNode();
		SpotLightNode* CreateSpotLightNode();
		MaterialNode* CreateMaterialNode();
		MeshNode* CreateMeshNode();
		SamplerNode* CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address);
		SamplerNode* CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address, uint32_t index);
		ShaderNode* CreateShaderNode();
		TextureNode* CreateTextureNode();
		TransformNode* CreateTransformNode(uint32_t bindIndex = 0);
		RasterizerStateNode* CreateRasterizerStateNode();
		RenderTargetNode* CreateRenderTargetNode(uint32_t index);
		BonesTransformsNode* CreateBonesTransformsNode();

		SceneNode& GetRoot() { return mRoot; }
		void Purge();

		void Update(float deltaTime);
		void Render();

	private:
		std::vector<SceneNode*> mNodes;

		Graphics::MatrixStack& mMatrixStack;

		SceneNode mRoot;

		friend class ModelNode;
	};

	
}// !namespace Graphics
}// !namespace ZERO


#endif //!INCLUDED_SIEGE_SCENEMANAGER_H