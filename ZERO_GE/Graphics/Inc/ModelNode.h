#ifndef INCLUDED_SCENE_MODELNODE_H
#define INCLUDED_SCENE_MODELNODE_H

#include "Model.h"
#include "MeshBuffer.h"
#include "SceneManager.h"


namespace ZERO
{
namespace Graphics
{

	class ModelNode : public SceneNode
	{
	public:

		ModelNode();
		virtual ~ModelNode();

		void Initialize(SceneManager* ScM, uint32_t diffuseMapBind = 0, uint32_t specularMapBind = 0,
						uint32_t displacementMapBind = 0, uint32_t normalMapBind = 0, 
						uint32_t materialBind = 0, uint32_t inputBind = 0, uint32_t boneBind = 0);

		void SetModel(Model* model) { mModel = model; }

		std::vector<Math::Matrix4>& GetBonesTransforms() { return mBonesTransforms; }
		void Terminate();

	protected:
		virtual void OnUpdate(float deltaTime);

	private:
		Model*						mModel;
		MeshBuffer*					mMeshBuffersModel;
		MeshNode**					mModelMeshNodes;
		Texture*					mDiffuseMaps;
		Texture*					mSpecularMaps;
		Texture*					mDisplacementMaps;
		Texture*					mNormalMaps;
		TextureNode**				mDiffuseMapNodes;
		TextureNode**				mSpecularMapNode;
		TextureNode**				mDisplacementMapNodes;
		TextureNode**				mNormalMapNodes;
		MaterialNode**				mModelMaterialNodes;
		BonesTransformsNode*		mBoneNode;
		SceneManager*				sm;

		uint32_t					boneRootIndex;
		std::vector<Math::Matrix4>	mBonesTransforms;
			
	};
}
}


#endif //#define INCLUDED_SCENE_MODELNODE_H
