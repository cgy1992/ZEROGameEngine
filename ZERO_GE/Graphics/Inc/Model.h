#ifndef INCLUDED_GRAPHICS_MODEL_H
#define INCLUDED_GRAPHICS_MODEL_H

#include <fstream>
#include <Graphics/Inc/Mesh.h>
#include <Graphics/Inc/SkinMesh.h>
#include <Graphics/Inc/Material.h>
#include <Graphics/Inc/Texture.h>
#include <Graphics/Inc/SimpleDraw.h>
#include "Bone.h"

namespace ZERO
{
namespace Graphics
{
class Model
{
public:
	Model();
	~Model();

	void Serialize(std::fstream& fs);
	void Deserialize(const char* filename);

	void SetNumberOfMeshes(int numberOfMeshes);
	uint32_t GetNumberOfMeshes() const { return nMeshes; }

	void SetNumberOfMaterials(int numberOfMaterials) { nMaterials = numberOfMaterials; }
	uint32_t GetNumberOfMaterials() const { return nMaterials; }

	void InsertMeshIndex(uint32_t index) { materialIndices.push_back(index); }
	uint32_t GetMaterialIndex(uint32_t meshIndex) { return materialIndices[meshIndex]; }

	std::vector<Bone*>& GetBonesVector() { return mBones; }
	void SetBoneRoot(uint32_t index) { mBoneIndex = index; mRoot = mBones[mBoneIndex]; }


	SkinMesh*& GetMesh() { return meshes; }
	Material*& GetMaterial() { return materials; }

	void SetNumberOfDiffuseMaps() { mNumberDiffuseMaps = static_cast<uint32_t>(mDiffuseMaps.size()); }
	void SetNumberOfSpecularMaps() { mNumberSpecularMaps = static_cast<uint32_t>(mSpecularMaps.size()); }
	void SetNumberOfDisplacementMaps() { mNumberDisplacementMaps = static_cast<uint32_t>(mDisplacementMaps.size()); }
	void SetNumberOfNormalMaps() { mNumberNormalMaps= static_cast<uint32_t>(mNormalMaps.size()); }

	uint32_t GetNumberOfDiffuseMaps() { return mNumberDiffuseMaps; }
	uint32_t GetNumberOfSpecularMaps() { return mNumberSpecularMaps; }
	uint32_t GetNumberOfDisplacementMaps() { return mNumberDisplacementMaps; }
	uint32_t GetNumberOfNormalMaps() { return mNumberNormalMaps; }

	std::map<uint32_t, std::string>& GetDiffuseMaps() { return mDiffuseMaps; }
	std::map<uint32_t, std::string>& GetSpecularMaps() { return mSpecularMaps; }
	std::map<uint32_t, std::string>& GetDisplacementMaps() { return mDisplacementMaps; }
	std::map<uint32_t, std::string>& GetNormalMaps() { return mNormalMaps; }

	uint32_t GetSelection() const { return mCurrentSelection; }

	bool IsSelectionMode() const { return mSelectionMode; }
	void ChangeSelectionMode();

	void NextSelection();
	void PreviousSelection();

	void Terminate();

private:
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void SerializeTextureMap(std::map<uint32_t, std::string>& textureMap, std::fstream& fs);
	void DeserializeTextureMap(std::map<uint32_t, std::string>& textureMap, uint32_t textureMapSize, std::fstream& fs);
	void SerializeBones(std::fstream& fs);
	void DeserializeBones(std::fstream& fs);

	void SerializeMatrix(Math::Matrix4& m, std::fstream& fs);
	void DeserializeMatrix(Math::Matrix4& m, std::fstream& fs);

	template<typename T>
	void MessageSerialize(T message, std::fstream& fs, size_t dataSize=sizeof(T))
	{
		char* messageBuffer = new char[dataSize];
		memcpy(messageBuffer, &message, dataSize);
		fs.write(messageBuffer, dataSize);
	}

	template<typename T>
	void MessageDeserialize(T& data, std::fstream& fs, size_t dataSize=sizeof(T))
	{
		fs.read((char*)&data, dataSize);
	}


	SkinMesh* meshes;
	uint32_t nMeshes;

	Material* materials;
	uint32_t nMaterials;
	std::vector<uint32_t> materialIndices;

	uint32_t mNumberDiffuseMaps;
	std::map<uint32_t, std::string> mDiffuseMaps;

	uint32_t mNumberSpecularMaps;
	std::map<uint32_t, std::string> mSpecularMaps;

	uint32_t mNumberDisplacementMaps;
	std::map<uint32_t, std::string> mDisplacementMaps;

	uint32_t mNumberNormalMaps;
	std::map<uint32_t, std::string> mNormalMaps;

	uint32_t mNumberOfBones;
	Bone* mRoot;
	std::vector<Bone*> mBones;
	uint32_t mBoneIndex;
	
	uint32_t mCurrentSelection;
	bool mSelectionMode;


};
}
}


#endif
