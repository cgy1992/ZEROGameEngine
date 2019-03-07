#include "Precompiled.h"
#include "Model.h"

using namespace ZERO;
using namespace ZERO::Graphics;

Model::Model()
	: nMeshes(0)
	, mCurrentSelection(0)
	, mSelectionMode(false)
{}

Model::~Model()
{


}

void Model::Terminate()
{
	for (uint32_t i = 0; i < nMeshes; ++i)
	{
		meshes[i].Destroy();
	}

	SafeDeleteArray(meshes);
	SafeDeleteArray(materials);
}

void Model::SetNumberOfMeshes(int numberOfMeshes)
{
	nMeshes = numberOfMeshes;
	materialIndices.reserve(nMeshes);
}

void Model::Serialize(std::fstream& fs)
{
	char nMeshesBuffer[sizeof(nMeshes)];
	memcpy(nMeshesBuffer, &nMeshes, sizeof(nMeshes));
	fs.write(nMeshesBuffer, sizeof(nMeshes));

	char nMaterialBuffer[sizeof(uint32_t)];
	memcpy(nMaterialBuffer, &nMaterials, sizeof(uint32_t));
	fs.write(nMaterialBuffer, sizeof(uint32_t));


	for (uint32_t i = 0; i < nMeshes; ++i)
	{
		const BoneVertex* vertices = meshes[i].GetVertices();
		const uint32_t* indices = meshes[i].GetIndices();

		uint32_t numVertices = meshes[i].GetVertexCount();
		uint32_t numIndices = meshes[i].GetIndicesCount();

		fs.write((char*)&numIndices, sizeof(uint32_t));
		fs.write((char*)&numVertices, sizeof(uint32_t));

		for (uint32_t vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
		{
			char vertexBuffer[sizeof(BoneVertex)];
			memcpy(vertexBuffer, &vertices[vertexIndex], sizeof(BoneVertex));
			fs.write(vertexBuffer, sizeof(BoneVertex));
		}

		for (uint32_t indicesIndex = 0; indicesIndex < numIndices; ++indicesIndex)
		{
			char indexBuffer[sizeof(uint32_t)];
			memcpy(indexBuffer, &indices[indicesIndex], sizeof(uint32_t));
			fs.write(indexBuffer, sizeof(uint32_t));
		}

		char materialIndexBuffer[sizeof(uint32_t)];
		memcpy(materialIndexBuffer, &materialIndices[i], sizeof(uint32_t));
		fs.write(materialIndexBuffer, sizeof(uint32_t));
	}

	for (uint32_t materialIndex = 0; materialIndex < nMaterials; ++materialIndex)
	{
		char materialBuffer[sizeof(Material)];
		memcpy(materialBuffer, &materials[materialIndex], sizeof(Material));
		fs.write(materialBuffer, sizeof(Material));
	}
	
	


	//Serializing Textures------------------------------------------
	char nDiffuse[sizeof(uint32_t)];
	memcpy(nDiffuse, &mNumberDiffuseMaps, sizeof(uint32_t));
	fs.write(nDiffuse, sizeof(uint32_t));

	char nSpecular [sizeof(uint32_t)];
	memcpy(nSpecular, &mNumberSpecularMaps, sizeof(uint32_t));
	fs.write(nSpecular, sizeof(uint32_t));

	char nDisplacement[sizeof(uint32_t)];
	memcpy(nDisplacement, &mNumberDisplacementMaps, sizeof(uint32_t));
	fs.write(nDisplacement, sizeof(uint32_t));

	char nNormal[sizeof(uint32_t)];
	memcpy(nNormal, &mNumberNormalMaps, sizeof(uint32_t));
	fs.write(nNormal, sizeof(uint32_t));

	SerializeTextureMap(mDiffuseMaps, fs);
	SerializeTextureMap(mSpecularMaps, fs);
	SerializeTextureMap(mDisplacementMaps, fs);
	SerializeTextureMap(mNormalMaps, fs);

	SerializeBones(fs);
}

void Model::Deserialize(const char* filename)
{
	char bufferName[128];
	sprintf_s(bufferName, sizeof(bufferName), "../Assets/Models/bin/%s", filename);

	std::fstream fs(bufferName, std::ios::in | std::ios::binary);

	fs.read((char*)&nMeshes, sizeof(nMeshes));
	fs.read((char*)&nMaterials, sizeof(uint32_t));

	meshes = new SkinMesh[nMeshes];
	materialIndices.reserve(nMeshes);
	materials = new Material[nMaterials];

	int i = 0;
	for(uint32_t i = 0; i < nMeshes; ++i)
	{	
		BoneVertex* vertices = nullptr;
		uint32_t vertexCount = 0;
		uint32_t* indices = nullptr;
		uint32_t indexCount = 0;

		fs.read((char*)&indexCount, sizeof(uint32_t));
		indices = new uint32_t[indexCount];

		fs.read((char*)&vertexCount, sizeof(uint32_t));
		vertices = new BoneVertex[vertexCount];
		
		for (uint32_t vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
		{
			char vertexBuffer[sizeof(BoneVertex)];
			fs.read(vertexBuffer, sizeof(BoneVertex));
			memcpy(&vertices[vertexIndex], vertexBuffer, sizeof(BoneVertex));
		}

		for (uint32_t indicesIndex = 0; indicesIndex < indexCount; ++indicesIndex)
		{
			char indexBuffer[sizeof(uint32_t)];
			fs.read(indexBuffer, sizeof(uint32_t));
			memcpy(&indices[indicesIndex], indexBuffer, sizeof(uint32_t));
		}

		char materialIndexBuffer[sizeof(uint32_t)];
		uint32_t index = 0;
		fs.read(materialIndexBuffer, sizeof(uint32_t));
		memcpy(&index, materialIndexBuffer, sizeof(uint32_t));
		materialIndices.push_back(index);

		meshes[i].Allocate(vertexCount, indexCount);
		meshes[i].SetIndices(indices);
		meshes[i].SetVertices(vertices);
	}

	for (uint32_t materialIndex = 0; materialIndex < nMaterials; ++materialIndex)
	{
		char materialBuffer[sizeof(Material)];
		fs.read(materialBuffer, sizeof(Material));
		memcpy(&materials[materialIndex], materialBuffer, sizeof(Material));
	}

	

	fs.read((char*)&mNumberDiffuseMaps, sizeof(uint32_t));
	fs.read((char*)&mNumberSpecularMaps, sizeof(uint32_t));
	fs.read((char*)&mNumberDisplacementMaps, sizeof(uint32_t));
	fs.read((char*)&mNumberNormalMaps, sizeof(uint32_t));

	DeserializeTextureMap(mDiffuseMaps, mNumberDiffuseMaps, fs);
	DeserializeTextureMap(mSpecularMaps, mNumberSpecularMaps, fs);
	DeserializeTextureMap(mDisplacementMaps, mNumberDisplacementMaps, fs);
	DeserializeTextureMap(mNormalMaps, mNumberNormalMaps, fs);

	DeserializeBones(fs);

	fs.close();
}


void Model::NextSelection()
{
	mCurrentSelection++;
	if (mCurrentSelection > nMeshes - 1)
	{
		mCurrentSelection = 0;
	}
}
void Model::PreviousSelection()
{
	mCurrentSelection--;
	if (mCurrentSelection < 0)
	{
		mCurrentSelection = nMeshes - 1;
	}
}

void Model::ChangeSelectionMode()
{
	if (mSelectionMode)
	{
		mSelectionMode = false;
	}
	else
	{
		mSelectionMode = true;
	}
}


//TODO : Serialize Textures is giving error;
void Model::SerializeTextureMap(std::map<uint32_t, std::string>& textureMap, std::fstream& fs)
{
	if (textureMap.size() > 0)
	{
		std::map<uint32_t, std::string>::iterator it;

		for (it = textureMap.begin(); it != textureMap.end(); it++)
		{
			char textureIndexBuffer[sizeof(uint32_t)];
			memcpy(textureIndexBuffer, &it->first, sizeof(uint32_t));
			fs.write(textureIndexBuffer, sizeof(uint32_t));

			char* c = new char[256];
			strcpy_s(c, 256, it->second.c_str());
			fs.write(c, 256);
		}
	}
	
}

//TODO : Deserialize Textures is giving error;
void Model::DeserializeTextureMap(std::map<uint32_t, std::string>& textureMap, uint32_t textureMapSize, std::fstream& fs)
{
	if (textureMapSize > 0)
	{
		for (uint32_t textureNumber = 0; textureNumber < textureMapSize; ++textureNumber)
		{
			uint32_t textureIndex = 0;
			fs.read((char*)&textureIndex, sizeof(uint32_t));

			char strName[256];
			fs.read(strName, 256);
			std::string textureName = strName;

			textureMap.try_emplace(textureIndex, textureName);
		}
	}
}


void Model::SerializeBones(std::fstream& fs)
{
	mNumberOfBones = static_cast<uint32_t>(mBones.size());
	MessageSerialize(mNumberOfBones, fs);
	for (uint32_t b = 0; b < mNumberOfBones; ++b)
	{
		char* c = new char[256];
		strcpy_s(c, 256, mBones[b]->name.c_str());
		fs.write(c, 256);
		MessageSerialize(mBones[b]->index, fs);
		MessageSerialize(mBones[b]->parentIndex, fs);
		MessageSerialize(mBones[b]->transform, fs);
		MessageSerialize(mBones[b]->offsetTransform, fs);

		MessageSerialize(mBones[b]->children.size(), fs);
		//Loop through children
		for (uint32_t i = 0; i < mBones[b]->children.size(); ++i)
		{
			MessageSerialize(mBones[b]->childrenIndex[i], fs);
		}

	}
}

void Model::DeserializeBones(std::fstream& fs)
{
	MessageDeserialize(mNumberOfBones, fs);

	Bone* bones = new Bone[mNumberOfBones];
	for (uint32_t b = 0; b < mNumberOfBones; ++b)
	{
		char strName[256];
		fs.read(strName, 256);
		bones[b].name = strName;
		MessageDeserialize(bones[b].index, fs);
		MessageDeserialize(bones[b].parentIndex, fs);
		MessageDeserialize(bones[b].transform, fs);
		MessageDeserialize(bones[b].offsetTransform, fs);
		

		uint32_t size;
		MessageDeserialize(size, fs);

		bones[b].childrenIndex.resize(size);

		//Loop through children
		for (uint32_t i = 0; i < size; ++i)
		{
			MessageDeserialize(bones[b].childrenIndex[i], fs);
		}
		mBones.push_back(&bones[b]);
	}

	for (uint32_t b = 0; b < mNumberOfBones; ++b)
	{
		Bone* bone = mBones[b];
		if (bone->parentIndex == -1)
		{
			mRoot = bone;
		}
		else
		{
			bone->parent = mBones[bone->parentIndex];
		}


		if (!bone->childrenIndex.empty())
		{
			for (uint32_t j = 0; j < bone->childrenIndex.size(); ++j)
			{
				bone->children.emplace_back(mBones[bone->childrenIndex[j]]);
			}
		}
	}
}


void Model::SerializeMatrix(Math::Matrix4& m, std::fstream& fs)
{
	MessageSerialize(m._11, fs); MessageSerialize(m._12, fs); MessageSerialize(m._13, fs); MessageSerialize(m._14, fs);
	MessageSerialize(m._21, fs); MessageSerialize(m._22, fs); MessageSerialize(m._23, fs); MessageSerialize(m._24, fs);
	MessageSerialize(m._31, fs); MessageSerialize(m._32, fs); MessageSerialize(m._33, fs); MessageSerialize(m._34, fs);
	MessageSerialize(m._41, fs); MessageSerialize(m._42, fs); MessageSerialize(m._43, fs); MessageSerialize(m._44, fs);
}

void Model::DeserializeMatrix(Math::Matrix4& m, std::fstream& fs)
{
	Math::Matrix4 m1;

	MessageDeserialize(m1._11, fs); MessageDeserialize(m1._12, fs); MessageDeserialize(m1._13, fs); MessageDeserialize(m1._14, fs);
	MessageDeserialize(m1._21, fs); MessageDeserialize(m1._22, fs); MessageDeserialize(m1._23, fs); MessageDeserialize(m1._24, fs);
	MessageDeserialize(m1._31, fs); MessageDeserialize(m1._32, fs); MessageDeserialize(m1._33, fs); MessageDeserialize(m1._34, fs);
	MessageDeserialize(m1._41, fs); MessageDeserialize(m1._42, fs); MessageDeserialize(m1._43, fs); MessageDeserialize(m1._44, fs);

	m = m1;
}