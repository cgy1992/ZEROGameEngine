#ifndef INCLUDED_GRAPHICS_TERRAIN_H
#define INCLUDED_GRAPHICS_TERRAIN_H

#include "HeightMap.h"
#include "Mesh.h"
#include "MeshBuffer.h"

namespace ZERO
{
namespace Graphics
{
class Terrain
{
public:
	Terrain();
	~Terrain();

	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;

	void Initialize(const char* filename, uint32_t columns, uint32_t rows, float maxHeight);
	MeshBuffer& GetMeshBuffer() { return mMeshBuffer; }
	void Terminate();
	void Render();

private:

	HeightMap mHeightMap;
	Mesh mMesh;
	MeshBuffer mMeshBuffer;

};
}
}



#endif // !INCLUDED_GRAPHICS_TERRAIN_H

