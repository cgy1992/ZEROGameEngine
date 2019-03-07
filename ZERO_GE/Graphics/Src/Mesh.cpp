#include "Precompiled.h"
#include "Mesh.h"

using namespace ZERO;
using namespace ZERO::Graphics;

Mesh::Mesh()
	:mVertices(nullptr)
	,mIndices(nullptr)
	,mNumVertices(0)
	,mNumIndices(0)
{
}

Mesh::~Mesh()
{
	ASSERT(mVertices == nullptr, "[Mesh] Vertices not freed.");
	ASSERT(mIndices == nullptr, "[Mesh] Indices not freed.");
}

void Mesh::Allocate(uint32_t numVertices, uint32_t numIndices)
{
	ASSERT(numVertices, "[Mesh] Invalid count.");
	ASSERT(numIndices, "[Mesh] Invalid count.");

	Destroy();

	mNumVertices = numVertices;
	mNumIndices = numIndices;

	mVertices = new Vertex[numVertices];
	mIndices = new uint32_t[numIndices];
}

void Mesh::Destroy()
{
	SafeDeleteArray(mVertices);
	SafeDeleteArray(mIndices);
	mNumVertices = 0;
	mNumIndices = 0;
}

Vertex& Mesh::GetVertex(uint32_t index)
{
	ASSERT(index < mNumVertices, "[Mesh] Invalid vertex.");
	return mVertices[index];
}

uint32_t& Mesh::GetIndex(uint32_t index)
{
	ASSERT(index < mNumIndices, "[Mesh] Invalid index.");
	return mIndices[index];
}

void Mesh::SetVertices(Vertex*& vertices)
{
	ASSERT(mVertices != nullptr, "[Mesh] Allocate memmory first for vertices.");
	mVertices = vertices;
}

void Mesh::SetIndices(uint32_t*& indices)
{
	ASSERT(mIndices != nullptr, "[Mesh] Allocate memmory first for indices.");
	mIndices = indices;
}
