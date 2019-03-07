#include "Precompiled.h"
#include "SkinMesh.h"

using namespace ZERO;
using namespace ZERO::Graphics;

SkinMesh::SkinMesh()
	:mVertices(nullptr)
	, mIndices(nullptr)
	, mNumVertices(0)
	, mNumIndices(0)
{
}

SkinMesh::~SkinMesh()
{
	ASSERT(mVertices == nullptr, "[Mesh] Vertices not freed.");
	ASSERT(mIndices == nullptr, "[Mesh] Indices not freed.");
}

void SkinMesh::Allocate(uint32_t numVertices, uint32_t numIndices)
{
	ASSERT(numVertices, "[Mesh] Invalid count.");
	ASSERT(numIndices, "[Mesh] Invalid count.");

	Destroy();

	mNumVertices = numVertices;
	mNumIndices = numIndices;

	mVertices = new BoneVertex[numVertices];
	mIndices = new uint32_t[numIndices];
}

void SkinMesh::Destroy()
{
	SafeDeleteArray(mVertices);
	SafeDeleteArray(mIndices);
	mNumVertices = 0;
	mNumIndices = 0;
}

BoneVertex& SkinMesh::GetVertex(uint32_t index)
{
	ASSERT(index < mNumVertices, "[Mesh] Invalid vertex.");
	return mVertices[index];
}

uint32_t& SkinMesh::GetIndex(uint32_t index)
{
	ASSERT(index < mNumIndices, "[Mesh] Invalid index.");
	return mIndices[index];
}

void SkinMesh::SetVertices(BoneVertex*& vertices)
{
	ASSERT(mVertices != nullptr, "[Mesh] Allocate memmory first for vertices.");
	mVertices = vertices;
}

void SkinMesh::SetIndices(uint32_t*& indices)
{
	ASSERT(mIndices != nullptr, "[Mesh] Allocate memmory first for indices.");
	mIndices = indices;
}
