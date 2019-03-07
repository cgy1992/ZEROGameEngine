#ifndef INCLUDED_SIEGE_SCENEMANAGER_H
#define INCLUDED_SIEGE_SCENEMANAGER_H


namespace ZERO
{
namespace SCENE
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
		DirectionalLightNode* CreateDirectionalLightNode();
		PointLightNode* CreatePointLightNode();
		SpotLightNode* CreateSpotLightNode();
		MaterialNode* CreateMaterialNode();
		MeshNode* CreateMeshNode();
		SamplerNode* CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address);
		ShaderNode* CreateShaderNode();
		TextureNode* CreateTextureNode();
		TransformNode* CreateTransformNode();

		void SetRoot(SceneNode* root);
		void Purge();

		void Update(float deltaTime);
		void Render();

	private:
		std::vector<SceneNode*> mNodes;

		Graphics::MatrixStack& mMatrixStack;

		SceneNode* mpRoot;
	};

}// !namespace SCENE
}// !namespace ZERO


#endif // #ifndef INCLUDED_SIEGE_SCENEMANAGER_H