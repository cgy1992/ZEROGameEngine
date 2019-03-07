#ifndef INCLUDED_MESHBUFFER_H
#define INCLUDED_MESHBUFFER_H

#include <Graphics\Inc\GraphicsSystem.h>

namespace ZERO
{
namespace Graphics
{

class Mesh;
class SkinMesh;

class MeshBuffer
{
public:
	MeshBuffer();
	~MeshBuffer();

	void Initialize(const Mesh& mesh);
	void Initialize(const SkinMesh& mesh);

	void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount);
	void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount);
	void SetMode(uint32_t mode) { mMode = mode; }
	void Terminate();
	void Render();


private:
	MeshBuffer(const MeshBuffer&) = delete;
	MeshBuffer& operator=(const MeshBuffer&) = delete;

	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	uint32_t mVertexSize;
	uint32_t mVertexCount;
	uint32_t mIndexCount;
	uint32_t mMode;
};

}// namespace Graphics
}//Namespace zero


#endif // !INCLUDED_MESHBUFFER_H
