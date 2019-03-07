#ifndef INCLUDED_GRAPHICS_MESH_H
#define INCLUDED_GRAPHICS_MESH_H

#include "VertexTypes.h"


namespace ZERO
{
namespace Graphics
{
class Mesh
{

public:
	Mesh();
	~Mesh();

	void Allocate(uint32_t numVertices, uint32_t numIndices);
	void Destroy();

	Vertex& GetVertex(uint32_t index);
	uint32_t& GetIndex(uint32_t index);

	const Vertex* GetVertices() const { return mVertices; }
	const uint32_t* GetIndices() const { return mIndices; }
	uint32_t GetVertexCount() const { return mNumVertices; }
	uint32_t GetIndicesCount() const { return mNumIndices; }

	void SetVertices(Vertex*& vertices);
	void SetIndices(uint32_t*& indices);

private:
	/*Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;*/

	Vertex* mVertices;
	uint32_t* mIndices;

	uint32_t mNumVertices;
	uint32_t mNumIndices;

};

}//namespace Graphics
}//Namespace ZERO

#endif // !INCLUDED_GRAPHICS_MESH_H
