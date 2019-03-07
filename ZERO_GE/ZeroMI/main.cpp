
#include <iostream>
#include <fstream>
#include <Core/Inc/Core.h>
#include <Math/Inc/ZeroMath.h>
#include <Graphics/Inc/Graphics.h>
#include <Graphics/Inc/Bone.h>
#include <Graphics/Inc/Model.h>
#include <Graphics/Inc/AnimationClip.h>
#include <Graphics/Inc/BoneAnimation.h>
#include <Graphics/Inc/Keyframe.h>
#include <assimp/Importer.hpp>//cpp importers 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define VerifyOrThrow(condition, message)\
	if(!(condition))\
	{\
		throw std::exception(message);\
	}\

namespace
{
	ZERO::Graphics::Model* model = nullptr;
	std::map<std::string, uint32_t> boneIndexMap;
	std::vector<uint32_t> numWeightsPerVertex;
	std::vector<ZERO::Graphics::AnimationClip> animationClips;
}

struct Params
{
	Params()
		:inputFileName(nullptr)
		, outputFileName(nullptr)
		, modelName(nullptr)
		, readingAnimation(nullptr)
	{}

	const char* inputFileName;
	const char* outputFileName;
	const char* modelName;
	const char* readingAnimation;
};




void PrintHelp()
{
	std::cout <<
		"==Model Importer Help==\n"
		<< "\n"
		<< "Usage: \n"
		<< "\n"
		<< "	ZeroMI.exe <InutFile> <OutputFile>\n"
		<< "\n";
	
}


ZERO::Math::Matrix4 Convert(aiMatrix4x4 transform)
{
	ZERO::Math::Matrix4 m;
	m._11 = static_cast<float>(transform.a1); m._12 = static_cast<float>(transform.b1); m._13 = static_cast<float>(transform.c1); m._14 = static_cast<float>(transform.d1);
	m._21 = static_cast<float>(transform.a2); m._22 = static_cast<float>(transform.b2); m._23 = static_cast<float>(transform.c2); m._24 = static_cast<float>(transform.d2);
	m._31 = static_cast<float>(transform.a3); m._32 = static_cast<float>(transform.b3); m._33 = static_cast<float>(transform.c3); m._34 = static_cast<float>(transform.d3);
	m._41 = static_cast<float>(transform.a4); m._42 = static_cast<float>(transform.b4); m._43 = static_cast<float>(transform.c4); m._44 = static_cast<float>(transform.d4);


	return m;
}


ZERO::Graphics::Bone* BuildSkeleton(aiNode& node, ZERO::Graphics::Bone* parent, ZERO::Graphics::Model& model)
{
	ZERO::Graphics::Bone* bone = nullptr;

	auto it = boneIndexMap.find(node.mName.C_Str());
	if (it == boneIndexMap.end())
	{
		const uint32_t boneIndex = model.GetBonesVector().size();

		//We need to add a new bone
		bone = new ZERO::Graphics::Bone();
		bone->index = boneIndex;
		bone->offsetTransform = ZERO::Math::Matrix4::Identity();

		if (node.mName.length > 0)
		{
			bone->name = node.mName.C_Str();
		}
		else
		{
			char buffer[128];
			sprintf_s(buffer, 128, "unnamed_%u", boneIndex);
			printf("Warning: Bone %u has no name, renamed to %s\n", boneIndex, buffer);
			bone->name = buffer;
		}

		model.GetBonesVector().push_back(bone);
		boneIndexMap.try_emplace(bone->name, bone->index);
	}
	else
	{
		bone = model.GetBonesVector()[it->second];
	}

	bone->transform = Convert(node.mTransformation);
	bone->parent = parent;
	if (bone->parent == nullptr)
	{
		bone->parentIndex = -1;
	}

	for (uint32_t i = 0; i < node.mNumChildren; ++i)
	{
		ZERO::Graphics::Bone* child = BuildSkeleton(*(node.mChildren[i]), bone, model);
		bone->childrenIndex.push_back(child->index);
		child->parentIndex = bone->index;
		bone->children.push_back(child);
	}

	return bone;
}



char* GetTextureName(const char* texturePath)
{
	const char* ptStart = texturePath;
	const char* ptEnd = texturePath;

	//Put ptEnd at the end of the word.
	while (*ptEnd != '\0')
	{
		ptEnd++;
	}

	while (*ptEnd != '\\' && *ptEnd != '\/' && strcmp(ptEnd, ptStart) != 0)
	{
		ptEnd--;
	}

	if (strcmp(ptEnd, ptStart) == 0)
	{
		return const_cast<char*>(ptEnd);
	}

	ptEnd++;

	return const_cast<char*>(ptEnd);
}




uint32_t GetBoneIndex(aiBone* bone, ZERO::Graphics::Model& model)
{
	auto iter = boneIndexMap.find(bone->mName.C_Str());
	if (iter != boneIndexMap.end())
	{
		return iter->second;
	}
	ZERO::Graphics::Bone* newBone = new ZERO::Graphics::Bone();
	newBone->name = bone->mName.C_Str();
	newBone->index = model.GetBonesVector().size();
	newBone->offsetTransform = Convert(bone->mOffsetMatrix);
	model.GetBonesVector().push_back(newBone);
	boneIndexMap.insert(std::make_pair(newBone->name, newBone->index));
	return newBone->index;
}


Params ParseArg(int argc, char* argv[])
{
	VerifyOrThrow(argc >= 5, "Invalid number of arguments.\n");

	Params params;
	params.inputFileName = argv[argc - 4];
	params.outputFileName = argv[argc - 3];
	params.modelName = argv[argc - 2];
	params.readingAnimation = argv[argc - 1];

	return params;
}

void ImportModel(const Params& params)
{

	//Creating a Model
	ZERO::Graphics::Model model;

	//Create an instance of the Importer class
	Assimp::Importer importer;

	const uint32_t flags =
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_MakeLeftHanded |
		aiProcess_FlipUVs |
		aiProcess_FlipWindingOrder;

	const aiScene* scene = importer.ReadFile(params.inputFileName, flags);

	//If the import failed, report it

	VerifyOrThrow(scene!=nullptr, importer.GetErrorString());

	//open a file
	std::fstream myFile;
	char buffer[50];
	sprintf_s(buffer, sizeof(buffer), "../Assets/Models/bin/%s%s", params.modelName, ".zerobin");

	//If it is reading a model
	if (strcmp(params.readingAnimation, "false") == 0)
	{
		myFile.open(buffer, std::ios::binary | std::ios::out);
	}

	//Read Mesh Data
	if (scene->HasMeshes())
	{
		std::cout << "Reading mesh data..\n";

		model.SetNumberOfMeshes(scene->mNumMeshes);

		model.GetMesh() = new ZERO::Graphics::SkinMesh[scene->mNumMeshes];



		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			const aiMesh* inputMesh = scene->mMeshes[meshIndex];

			auto vertices = std::make_unique<ZERO::Graphics::BoneVertex[]>(inputMesh->mNumVertices);

			model.GetMesh()[meshIndex].Allocate(inputMesh->mNumVertices, inputMesh->mNumFaces * 3);

			//Position
			for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
			{
				auto& vertex = vertices[i];
				vertex.position.x = inputMesh->mVertices[i].x;
				vertex.position.y = inputMesh->mVertices[i].y;
				vertex.position.z = inputMesh->mVertices[i].z;

				model.GetMesh()[meshIndex].GetVertex(i).position.x = inputMesh->mVertices[i].x;
				model.GetMesh()[meshIndex].GetVertex(i).position.y = inputMesh->mVertices[i].y;
				model.GetMesh()[meshIndex].GetVertex(i).position.z = inputMesh->mVertices[i].z;


			}


			//Tangents
			if (inputMesh->HasTangentsAndBitangents())
			{
				std::cout << "Reading tangents...\n";

				for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
				{
					auto& vertex = vertices[i];
					vertex.tangent.x = inputMesh->mTangents[i].x;
					vertex.tangent.y = inputMesh->mTangents[i].y;
					vertex.tangent.z = inputMesh->mTangents[i].z;

					model.GetMesh()[meshIndex].GetVertex(i).tangent.x = inputMesh->mTangents[i].x;
					model.GetMesh()[meshIndex].GetVertex(i).tangent.y = inputMesh->mTangents[i].y;
					model.GetMesh()[meshIndex].GetVertex(i).tangent.z = inputMesh->mTangents[i].z;
				}
			}

			//UVs
			if (inputMesh->HasTextureCoords(0))
			{
				std::cout << "Reading Uvs...\n";

				for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
				{
					auto& vertex = vertices[i];
					vertex.uv.x = inputMesh->mTextureCoords[0][i].x;
					vertex.uv.y = inputMesh->mTextureCoords[0][i].y;

					model.GetMesh()[meshIndex].GetVertex(i).uv.x = inputMesh->mTextureCoords[0][i].x;
					model.GetMesh()[meshIndex].GetVertex(i).uv.y = inputMesh->mTextureCoords[0][i].y;
				}
			}

			//Indices
			std::cout << "Reading Indices\n";

			auto indices = std::make_unique<uint32_t[]>(inputMesh->mNumFaces * 3);


			for (uint32_t face = 0, index = 0; face < inputMesh->mNumFaces; ++face, index += 3)
			{
				indices[index] = inputMesh->mFaces[face].mIndices[0];
				indices[index + 1] = inputMesh->mFaces[face].mIndices[1];
				indices[index + 2] = inputMesh->mFaces[face].mIndices[2];

				model.GetMesh()[meshIndex].GetIndex(index) = indices[index];
				model.GetMesh()[meshIndex].GetIndex(index + 1) = indices[index + 1];
				model.GetMesh()[meshIndex].GetIndex(index + 2) = indices[index + 2];
			}



			//Normals
			if (inputMesh->HasNormals())
			{
				std::cout << "Reading normals...\n";

				for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
				{
					auto& vertex = vertices[i];
					vertex.normal.x = inputMesh->mNormals[i].x;
					vertex.normal.y = inputMesh->mNormals[i].y;
					vertex.normal.z = inputMesh->mNormals[i].z;

					model.GetMesh()[meshIndex].GetVertex(i).normal.x = inputMesh->mNormals[i].x;
					model.GetMesh()[meshIndex].GetVertex(i).normal.y = inputMesh->mNormals[i].y;
					model.GetMesh()[meshIndex].GetVertex(i).normal.z = inputMesh->mNormals[i].z;
				}
			}
			else
			{
				ZERO::Graphics::GraphicsUtil::ComputeNormals(model.GetMesh()[meshIndex]);
			}

			model.InsertMeshIndex(inputMesh->mMaterialIndex);


			//Bones
			if (inputMesh->HasBones())
			{

				numWeightsPerVertex.resize(inputMesh->mNumVertices, 0);

				for (uint32_t i = 0; i < inputMesh->mNumBones; ++i)
				{
					aiBone* bone = inputMesh->mBones[i];

					uint32_t boneIndex = GetBoneIndex(bone, model);
					uint32_t boneVertexId;
					float weight;
					for (uint32_t j = 0; j < bone->mNumWeights; ++j)
					{
						auto& aiVertexWeight = bone->mWeights[j];
						boneVertexId = aiVertexWeight.mVertexId;
						weight = aiVertexWeight.mWeight;
						if (numWeightsPerVertex[boneVertexId] < 4)
						{

							model.GetMesh()[meshIndex].GetVertex(boneVertexId).boneWeight[numWeightsPerVertex[boneVertexId]] = weight;
							model.GetMesh()[meshIndex].GetVertex(boneVertexId).boneIndex[numWeightsPerVertex[boneVertexId]] = boneIndex;
							numWeightsPerVertex[boneVertexId]++;

						}

					}
				}
			}

		}
	}

	
	if (scene->HasMaterials())
	{
		auto material = scene->mMaterials;
		model.SetNumberOfMaterials(scene->mNumMaterials);
		model.GetMaterial() = new ZERO::Graphics::Material[scene->mNumMaterials];

		int numTextures = 0;

		uint32_t indexDiffuse{ 0 };
		uint32_t indexSpecular{ 0 };
		uint32_t indexDisplacement{ 0 };
		uint32_t indexNormal{ 0 };

		for (uint32_t i = 0; i < scene->mNumMaterials; ++i)
		{
			aiColor3D ambient(0.f, 0.f, 0.f);
			aiColor3D diffuse(0.f, 0.f, 0.f);
			aiColor3D specular(0.f, 0.f, 0.f);
			aiColor3D emissive(0.f, 0.f, 0.f);
			float power = 0.0f;

			material[i]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			material[i]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			material[i]->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			material[i]->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
			material[i]->Get(AI_MATKEY_SHININESS, power);
			if (power == 0.0f)
			{
				power = 1.0f;
			}

			if (strcmp(params.readingAnimation, "false") == 0)
			{
				aiString Path;
				if (material[i]->GetTexture(aiTextureType_DIFFUSE, 0, &Path) == AI_SUCCESS)
				{
					std::string filePath;
					filePath = Path.data;


					if (filePath[0] == '*')
					{
						std::string texturePath = "../Assets/Models/";
						texturePath += "/";
						texturePath += params.outputFileName;
						texturePath += "/";
						texturePath += params.modelName;
						texturePath += "_diffuse_";
						texturePath += std::to_string(indexDiffuse);
						indexDiffuse++;

						ASSERT(scene->HasTextures(), "Error, No embeded textures foud.");

						int textureIndex = std::atoi(filePath.c_str() + 1);
						ASSERT(textureIndex < (int)scene->mNumTextures, "Error: Invalid Texture index.");

						const aiTexture* texture = scene->mTextures[textureIndex];
						ASSERT(texture->mHeight == 0, "Error: Umcompressed texture files");

						texturePath += ".";
						texturePath += texture->achFormatHint;


						std::cout << "Infor: Extracting embedded texture " << texturePath.c_str() << ".";

						FILE* file = nullptr;
						fopen_s(&file, texturePath.c_str(), "wb");
						size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
						ASSERT(written == texture->mWidth, "Error: Failed to extract embedded texture");
						fclose(file);

						model.GetDiffuseMaps().try_emplace(i, texturePath.c_str());
					}
					else
					{
						char* buffer = new char[255];
						memcpy(buffer, "../Assets/Models", 255);
						strcat(buffer, "/");
						strcat(buffer, params.outputFileName);
						strcat(buffer, "/");
						strcat(buffer, filePath.c_str());
						model.GetDiffuseMaps().try_emplace(i, buffer);
					}

				}

				if (material[i]->GetTexture(aiTextureType_DISPLACEMENT, 0, &Path) == AI_SUCCESS)
				{
					std::string filePath;
					filePath = Path.data;


					if (filePath[0] == '*')
					{
						std::string texturePath = "../Assets/Models/";
						texturePath += "/";
						texturePath += params.outputFileName;
						texturePath += "/";
						texturePath += params.modelName;
						texturePath += "_displacement_";
						texturePath += std::to_string(indexDisplacement);
						indexDisplacement++;

						ASSERT(scene->HasTextures(), "Error, No embeded textures foud.");

						int textureIndex = std::atoi(filePath.c_str() + 1);
						ASSERT(textureIndex < (int)scene->mNumTextures, "Error: Invalid Texture index.");

						const aiTexture* texture = scene->mTextures[textureIndex];
						ASSERT(texture->mHeight == 0, "Error: Umcompressed texture files");

						texturePath += ".";
						texturePath += texture->achFormatHint;


						std::cout << "Infor: Extracting embedded texture " << texturePath.c_str() << ".";

						FILE* file = nullptr;
						fopen_s(&file, texturePath.c_str(), "wb");
						size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
						ASSERT(written == texture->mWidth, "Error: Failed to extract embedded texture");
						fclose(file);

						model.GetDisplacementMaps().try_emplace(i, texturePath.c_str());
					}
					else
					{
						char* buffer = new char[255];
						memcpy(buffer, "../Assets/Models", 255);
						strcat(buffer, "/");
						strcat(buffer, params.outputFileName);
						strcat(buffer, "/");
						strcat(buffer, filePath.c_str());
						model.GetDisplacementMaps().try_emplace(i, buffer);
					}
				}

				if (material[i]->GetTexture(aiTextureType_SPECULAR, 0, &Path) == AI_SUCCESS)
				{
					std::string filePath;
					filePath = Path.data;


					if (filePath[0] == '*')
					{
						std::string texturePath = "../Assets/Models/";
						texturePath += "/";
						texturePath += params.outputFileName;
						texturePath += "/";
						texturePath += params.modelName;
						texturePath += "_specular_";
						texturePath += std::to_string(indexSpecular);
						indexSpecular++;

						ASSERT(scene->HasTextures(), "Error, No embeded textures foud.");

						int textureIndex = std::atoi(filePath.c_str() + 1);
						ASSERT(textureIndex < (int)scene->mNumTextures, "Error: Invalid Texture index.");

						const aiTexture* texture = scene->mTextures[textureIndex];
						ASSERT(texture->mHeight == 0, "Error: Umcompressed texture files");

						texturePath += ".";
						texturePath += texture->achFormatHint;


						std::cout << "Infor: Extracting embedded texture " << texturePath.c_str() << ".";

						FILE* file = nullptr;
						fopen_s(&file, texturePath.c_str(), "wb");
						size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
						ASSERT(written == texture->mWidth, "Error: Failed to extract embedded texture");
						fclose(file);

						model.GetSpecularMaps().try_emplace(i, texturePath.c_str());
					}
					else
					{
						char* buffer = new char[255];
						memcpy(buffer, "../Assets/Models", 255);
						strcat(buffer, "/");
						strcat(buffer, params.outputFileName);
						strcat(buffer, "/");
						strcat(buffer, filePath.c_str());
						model.GetSpecularMaps().try_emplace(i, buffer);
					}
				}

				if (material[i]->GetTexture(aiTextureType_NORMALS, 0, &Path) == AI_SUCCESS)
				{
					std::string filePath;
					filePath = Path.data;


					if (filePath[0] == '*')
					{
						std::string texturePath = "../Assets/Models/";
						texturePath += "/";
						texturePath += params.outputFileName;
						texturePath += "/";
						texturePath += params.modelName;
						texturePath += "_normal_";
						texturePath += std::to_string(indexNormal);
						indexNormal++;

						ASSERT(scene->HasTextures(), "Error, No embeded textures foud.");

						int textureIndex = std::atoi(filePath.c_str() + 1);
						ASSERT(textureIndex < (int)scene->mNumTextures, "Error: Invalid Texture index.");

						const aiTexture* texture = scene->mTextures[textureIndex];
						ASSERT(texture->mHeight == 0, "Error: Umcompressed texture files");

						texturePath += ".";
						texturePath += texture->achFormatHint;


						std::cout << "Infor: Extracting embedded texture " << texturePath.c_str() << ".";

						FILE* file = nullptr;
						fopen_s(&file, texturePath.c_str(), "wb");
						size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
						ASSERT(written == texture->mWidth, "Error: Failed to extract embedded texture");
						fclose(file);

						model.GetNormalMaps().try_emplace(i, texturePath.c_str());
					}
					else
					{
						char* buffer = new char[255];
						memcpy(buffer, "../Assets/Models", 255);
						strcat(buffer, "/");
						strcat(buffer, params.outputFileName);
						strcat(buffer, "/");
						strcat(buffer, filePath.c_str());
						model.GetNormalMaps().try_emplace(i, buffer);
					}
				}
			}

			model.GetMaterial()[i].ambient = { ambient.r, ambient.g, ambient.b, 1.0f };
			model.GetMaterial()[i].diffuse = { diffuse.r, diffuse.g, diffuse.b, 1.0f };
			model.GetMaterial()[i].specular = { specular.r, specular.g, specular.b, 1.0f };
			model.GetMaterial()[i].emissive = { emissive.r, emissive.g, emissive.b, 1.0f };
			model.GetMaterial()[i].power = { power };
		}

		if (strcmp(params.readingAnimation, "false") == 0)
		{
			model.SetNumberOfDiffuseMaps();
			model.SetNumberOfSpecularMaps();
			model.SetNumberOfDisplacementMaps();
			model.SetNumberOfNormalMaps();
		}
	}
	

	if (scene->HasAnimations())
	{
		ZERO::Graphics::Bone* root = BuildSkeleton(*scene->mRootNode, nullptr, model);

		//Traversing through the number of animations
		ASSERT(scene->mNumAnimations != 0, "Error: No Animations found in the file");
		animationClips.resize(scene->mNumAnimations);
		for (uint32_t animationIndex = 0; animationIndex < scene->mNumAnimations; ++animationIndex)
		{

			aiAnimation* animation = scene->mAnimations[animationIndex];
			ASSERT(animation != nullptr, "Error: Could not access the animation");
			animationClips[animationIndex].duration = static_cast<float>(animation->mDuration);
			animationClips[animationIndex].ticksPerSecond = static_cast<float>(animation->mTicksPerSecond);
			animationClips[animationIndex].name = animation->mName.data;
			animationClips[animationIndex].totalNumberOfBones = boneIndexMap.size();
			animationClips[animationIndex].numberOfBonesWithAnim = animation->mNumChannels;

			std::cout << "Loading animation " << animation->mName.data << ".\n";
			//Traversing through the number of channels
			for (uint32_t channelIndex = 0; channelIndex < animation->mNumChannels; ++channelIndex)
			{
				animationClips[animationIndex].boneAnimations.resize(boneIndexMap.size(), nullptr);
				ZERO::Graphics::BoneAnimation* newBoneAnim = new ZERO::Graphics::BoneAnimation();

				auto channel = animation->mChannels[channelIndex];

				std::string name = channel->mNodeName.data;
				auto it = boneIndexMap.find(name.c_str());

				if (it != boneIndexMap.end())
				{
					newBoneAnim->boneIndex = it->second;
				}
				else
				{
					newBoneAnim->boneIndex = -999;
				}

				std::cout << "Loading Position for " << channel->mNodeName.data << " bone.\n";
				//Getting Positions
				for (uint32_t posIndex = 0; posIndex < channel->mNumPositionKeys; ++posIndex)
				{
					ZERO::Graphics::Keyframe<ZERO::Math::Vector3> keyPos;
					keyPos.timer = static_cast<float>(channel->mPositionKeys[posIndex].mTime / animationClips[animationIndex].ticksPerSecond);
					aiVector3D pos = channel->mPositionKeys[posIndex].mValue;
					keyPos.SetValue({ pos.x, pos.y, pos.z });
					newBoneAnim->AddPositionKey(keyPos);
				}

				std::cout << "Loading Scale for " << channel->mNodeName.data << " bone.\n";
				//Getting Scales
				for (uint32_t scaleIndex = 0; scaleIndex < channel->mNumScalingKeys; ++scaleIndex)
				{
					ZERO::Graphics::Keyframe<ZERO::Math::Vector3> keyScale;
					keyScale.timer = static_cast<float>(channel->mScalingKeys[scaleIndex].mTime / animationClips[animationIndex].ticksPerSecond);
					aiVector3D scale = channel->mScalingKeys[scaleIndex].mValue;
					keyScale.SetValue({ scale.x, scale.y, scale.z });
					newBoneAnim->AddScaleKey(keyScale);
				}

				std::cout << "Loading Rotation for " << channel->mNodeName.data << " bone.\n";
				//Getting Rotations
				for (uint32_t rotIndex = 0; rotIndex < channel->mNumRotationKeys; ++rotIndex)
				{
					ZERO::Graphics::Keyframe<ZERO::Math::Quaternion> keyRot;
					keyRot.timer = static_cast<float>(channel->mRotationKeys[rotIndex].mTime / animationClips[animationIndex].ticksPerSecond);
					aiQuaternion rot = channel->mRotationKeys[rotIndex].mValue;
					keyRot.SetValue({ rot.x, rot.y, rot.z, rot.w });
					newBoneAnim->AddRotationKey(keyRot);
				}

				animationClips[animationIndex].boneAnimations[it->second] = newBoneAnim;
			}
		}
	}

	//If it is reading a model
	if (strcmp(params.readingAnimation, "false") == 0)
	{
		model.Serialize(myFile);
		myFile.close();
	}

	//Serializing animation
	if (strcmp(params.readingAnimation, "true") == 0)
	{
		for (uint32_t i = 0; i < animationClips.size(); ++i)
		{
			animationClips[i].SerializeAnim();
		}
	}

	//Destroying meshes
	model.Terminate();
	return;
}




int main(int argc, char* argv[])
{
	try
	{
		const Params params = ParseArg(argc, argv);
		ImportModel(params);
	}
	catch(std::exception e)
	{
		printf("Exception: %s", e.what());
	}

	

	return 0;
}