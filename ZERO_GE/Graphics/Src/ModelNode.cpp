#include "Precompiled.h"
#include "ModelNode.h"


using namespace ZERO;
using namespace ZERO::Graphics;

ModelNode::ModelNode()
		:	mMeshBuffersModel		(nullptr)
		,	mModelMeshNodes			(nullptr)
		,	mDiffuseMaps			(nullptr)
		,	mSpecularMaps			(nullptr)
		,	mDisplacementMaps		(nullptr)
		,	mNormalMaps				(nullptr)
		,	mDiffuseMapNodes		(nullptr)
		,	mSpecularMapNode		(nullptr)
		,	mDisplacementMapNodes	(nullptr)
		,	mNormalMapNodes			(nullptr)
		,	mModelMaterialNodes		(nullptr)
		,	mModel					(nullptr)
		,	mBoneNode				(nullptr)
{}

ModelNode::~ModelNode()
{}

void ModelNode::Initialize(SceneManager* ScM, uint32_t diffuseMapBind, uint32_t specularMapBind,
							uint32_t displacementMapBind, uint32_t normalMapBind, 
							uint32_t materialBind, uint32_t inputBind, uint32_t boneBind)
{	
	ASSERT(mModel != nullptr, "[ModelNode]Before initialize, you should set the model.");
	ScM->mNodes.push_back(this);
    
	//Creating mesh node
	mMeshBuffersModel = new MeshBuffer[mModel->GetNumberOfMeshes()];
	for (uint32_t i = 0; i < mModel->GetNumberOfMeshes(); i++)
	{
		mMeshBuffersModel[i].Initialize(mModel->GetMesh()[i]);
	}

	char name[64];
	mModelMeshNodes = new MeshNode*[mModel->GetNumberOfMeshes()];
	for (uint32_t i = 0; i < mModel->GetNumberOfMeshes(); i++)
	{
		sprintf_s(name, "Mesh_%u", i);
		mModelMeshNodes[i] = ScM->CreateMeshNode();
		mModelMeshNodes[i]->SetName(name);
		mModelMeshNodes[i]->SetId(i);
		mModelMeshNodes[i]->SetRenderMesh(&mMeshBuffersModel[i]);

	}

	//Creating boneNode
	mBoneNode = ScM->CreateBonesTransformsNode();
	mBoneNode->Initialize(boneBind);
	mBonesTransforms.resize(mModel->GetBonesVector().size());
	for (uint32_t i = 0; i < mModel->GetBonesVector().size(); ++i)
	{
		Bone* bone = mModel->GetBonesVector()[i];
		mBonesTransforms[i] = bone->transform;
		while (bone->parent)
		{
			mBonesTransforms[i] = mBonesTransforms[i] * bone->parent->transform;
			bone = bone->parent;
		}
	}

	for (uint32_t i = 0; i < mBonesTransforms.size(); ++i)
	{
		Bone* bone = mModel->GetBonesVector()[i];
		mBoneNode->SetTransform(i, bone->offsetTransform * mBonesTransforms[i]);
	}

	this->AddChild(mBoneNode);



	mModelMaterialNodes = new MaterialNode*[mModel->GetNumberOfMeshes()];
	for (uint32_t i = 0; i < mModel->GetNumberOfMeshes(); ++i)
	{
		mModelMaterialNodes[i] = ScM->CreateMaterialNode();
		mModelMaterialNodes[i]->Initialize(materialBind);
		mModelMaterialNodes[i]->GetMaterial().ambient = mModel->GetMaterial()[mModel->GetMaterialIndex(i)].ambient;
		mModelMaterialNodes[i]->GetMaterial().diffuse = mModel->GetMaterial()[mModel->GetMaterialIndex(i)].diffuse;
		mModelMaterialNodes[i]->GetMaterial().specular = mModel->GetMaterial()[mModel->GetMaterialIndex(i)].specular;
		mModelMaterialNodes[i]->GetMaterial().emissive = mModel->GetMaterial()[mModel->GetMaterialIndex(i)].emissive;
		mModelMaterialNodes[i]->GetMaterial().power = mModel->GetMaterial()[mModel->GetMaterialIndex(i)].power;

		mBoneNode->AddChild(mModelMaterialNodes[i]);
	}

	uint32_t numberDiffuse, numberSpecular, numberDisplacement, numberNormal;

	numberDiffuse = mModel->GetNumberOfDiffuseMaps();
	numberSpecular = mModel->GetNumberOfSpecularMaps();
	numberDisplacement = mModel->GetNumberOfDisplacementMaps();
	numberNormal = mModel->GetNumberOfNormalMaps();

	if (numberDiffuse != 0)
	{
		mDiffuseMaps = new Texture[numberDiffuse];
		mDiffuseMapNodes = new TextureNode*[numberDiffuse];
		std::map<uint32_t, std::string>::iterator it;
		uint32_t i = 0;
		for (it = mModel->GetDiffuseMaps().begin(); it != mModel->GetDiffuseMaps().end(); it++)
		{
			mDiffuseMaps[i].Initialize(it->second.c_str(), diffuseMapBind);
			mDiffuseMaps[i].SetTextureType(Graphics::Texture::TextureType::DiffuseMap);
			mDiffuseMapNodes[i] = ScM->CreateTextureNode();
			mDiffuseMapNodes[i]->SetTexture(&mDiffuseMaps[i]);
			mDiffuseMapNodes[i]->SetName(it->second.c_str());
			++i;
		}
	}

	if (numberSpecular != 0)
	{
		mSpecularMaps = new Texture[numberSpecular];
		mSpecularMapNode = new TextureNode*[numberSpecular];
		std::map<uint32_t, std::string>::iterator it;
		uint32_t i = 0;
		for (it = mModel->GetSpecularMaps().begin(); it != mModel->GetSpecularMaps().end(); it++)
		{
			mSpecularMaps[i].SetTextureType(Graphics::Texture::TextureType::SpecularMap);
			mSpecularMaps[i].Initialize(it->second.c_str(), specularMapBind);
			mSpecularMapNode[i] = ScM->CreateTextureNode();
			mSpecularMapNode[i]->SetTexture(&mSpecularMaps[i]);
			mSpecularMapNode[i]->SetName(it->second.c_str());
			++i;
		}
	}

	if (numberDisplacement != 0)
	{
		mDisplacementMaps = new Texture[numberDisplacement];
		mDisplacementMapNodes = new TextureNode*[numberDisplacement];
		std::map<uint32_t, std::string>::iterator it;
		uint32_t i = 0;
		for (it = mModel->GetDisplacementMaps().begin(); it != mModel->GetDisplacementMaps().end(); it++)
		{
			mDisplacementMaps[i].SetTextureType(Graphics::Texture::TextureType::DisplacementMap);
			mDisplacementMaps[i].Initialize(it->second.c_str(), displacementMapBind);
			mDisplacementMapNodes[i] = ScM->CreateTextureNode();
			mDisplacementMapNodes[i]->SetTexture(&mDisplacementMaps[i]);
			mDisplacementMapNodes[i]->SetName(it->second.c_str());
			++i;
		}
	}

	if (numberNormal != 0)
	{
		mNormalMaps = new Texture[numberNormal];
		mNormalMapNodes = new TextureNode*[numberNormal];
		std::map<uint32_t, std::string>::iterator it;
		uint32_t i = 0;
		for (it = mModel->GetNormalMaps().begin(); it != mModel->GetNormalMaps().end(); it++)
		{
			mNormalMaps[i].SetTextureType(Graphics::Texture::TextureType::NormalMap);
			mNormalMaps[i].Initialize(it->second.c_str(), normalMapBind);
			mNormalMapNodes[i] = ScM->CreateTextureNode();
			mNormalMapNodes[i]->SetTexture(&mNormalMaps[i]);
			mNormalMapNodes[i]->SetName(it->second.c_str());
			++i;
		}
	}


	//Nodes Connections
	for (uint32_t i = 0; i < mModel->GetNumberOfMeshes(); i++)
	{
		//Bones Initialization
		std::map<uint32_t, std::string>::iterator itDiffuse = mModel->GetDiffuseMaps().begin();
		std::map<uint32_t, std::string>::iterator itSpecular = mModel->GetSpecularMaps().begin();
		std::map<uint32_t, std::string>::iterator itDisplacement = mModel->GetDisplacementMaps().begin();
		std::map<uint32_t, std::string>::iterator itNormal = mModel->GetNormalMaps().begin();

		uint32_t indexDiffuse = 0;
		uint32_t indexSpecular = 0;
		uint32_t indexDisplacement = 0;
		uint32_t indexNormal = 0;

		bool foundDiffuse = false;
		bool foundSpecular = false;
		bool foundDisplacement = false;
		bool foundNormal = false;

		for (itDiffuse; itDiffuse != mModel->GetDiffuseMaps().end(); ++itDiffuse)
		{
			if (itDiffuse->first == mModel->GetMaterialIndex(i))
			{
				foundDiffuse = true;
				break;
			}
			indexDiffuse++;
		}

		for (itSpecular; itSpecular != mModel->GetSpecularMaps().end(); ++itSpecular)
		{
			if (itSpecular->first == mModel->GetMaterialIndex(i))
			{
				foundSpecular = true;
				break;
			}
			indexSpecular++;
		}

		for (itDisplacement; itDisplacement != mModel->GetDisplacementMaps().end(); ++itDisplacement)
		{
			if (itDisplacement->first == mModel->GetMaterialIndex(i))
			{
				foundDisplacement = true;
				break;
			}
			indexDisplacement++;
		}

		for (itNormal; itNormal != mModel->GetNormalMaps().end(); ++itNormal)
		{
			if (itNormal->first == mModel->GetMaterialIndex(i))
			{
				foundNormal = true;
				break;
			}
			indexNormal++;
		}

		SceneNode* it = mModelMaterialNodes[i];

		if (foundDiffuse)
		{
			mModelMaterialNodes[i]->GetMaterial().hasDiffuseMap = 1;
			it->AddChild(mDiffuseMapNodes[indexDiffuse]);
			it = mDiffuseMapNodes[indexDiffuse];
				//mDiffuseMapNodes[indexDiffuse]->AddChild(mModelMeshNodes[i]);
		}

		if (foundNormal)
		{
			mModelMaterialNodes[i]->GetMaterial().hasNormalMap = 1;
			it->AddChild(mNormalMapNodes[indexNormal]);
			it = mNormalMapNodes[indexNormal];
				//mNormalMapNodes[indexNormal]->AddChild(mModelMeshNodes[i]);			
		}

		if (foundSpecular)
		{
			mModelMaterialNodes[i]->GetMaterial().hasSpecularMap = 1;
			it->AddChild(mSpecularMapNode[indexSpecular]);
			it = mSpecularMapNode[indexSpecular];
			//mSpecularMapNode[indexSpecular]->AddChild(mModelMeshNodes[i]);
		}

		if (foundDisplacement)
		{
			mModelMaterialNodes[i]->GetMaterial().hasDisplacementMap = 1;
			it->AddChild(mDisplacementMapNodes[indexDisplacement]);
			it = mDisplacementMapNodes[indexDisplacement];
			//mDisplacementMapNodes[indexDisplacement]->AddChild(mModelMeshNodes[i]);
		}

		it->AddChild(mModelMeshNodes[i]);
	}
}

void ModelNode::Terminate()
{
	for (uint32_t i = 0; i < mModel->GetNumberOfMeshes(); ++i)
	{
		mMeshBuffersModel[i].Terminate();
		mModelMaterialNodes[i]->Terminate();
	}

	SafeDeleteArray(mModelMeshNodes);

	if (mModel->GetNumberOfDiffuseMaps() > 0)
	{
		for (uint32_t i = 0; i < mModel->GetNumberOfDiffuseMaps(); ++i)
		{
			mDiffuseMaps[i].Terminate();
		}

		SafeDeleteArray(mDiffuseMapNodes);
	}

	if (mModel->GetNumberOfSpecularMaps() > 0)
	{
		for (uint32_t i = 0; i < mModel->GetNumberOfSpecularMaps(); ++i)
		{
			mSpecularMaps[i].Terminate();
		}

		SafeDeleteArray(mSpecularMapNode);
	}

	if (mModel->GetNumberOfDisplacementMaps() > 0)
	{
		for (uint32_t i = 0; i < mModel->GetNumberOfDisplacementMaps(); ++i)
		{
			mDisplacementMaps[i].Terminate();
		}

		SafeDeleteArray(mDisplacementMapNodes);
	}

	if (mModel->GetNumberOfNormalMaps() > 0)
	{
		for (uint32_t i = 0; i < mModel->GetNumberOfNormalMaps(); ++i)
		{
			mNormalMaps[i].Terminate();
		}

		SafeDeleteArray(mNormalMapNodes);
	}

	mBoneNode->Terminate();

}

void ModelNode::OnUpdate(float deltaTime)
{
	for (uint32_t i = 0; i < mModel->GetBonesVector().size(); ++i)
	{
		Bone* bone = mModel->GetBonesVector()[i];
		mBonesTransforms[i] = bone->transform;
		while (bone->parent)
		{
			mBonesTransforms[i] = mBonesTransforms[i] * bone->parent->transform;
			bone = bone->parent;
		}
	}

	for (uint32_t i = 0; i < mBonesTransforms.size(); ++i)
	{
		Bone* bone = mModel->GetBonesVector()[i];
		mBoneNode->SetTransform(i, bone->offsetTransform * mBonesTransforms[i]);
	}
}
