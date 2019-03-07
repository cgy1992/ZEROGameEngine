#ifndef INCLUDED_GRAPHICS_SKINMESH_H
#define INCLUDED_GRAPHICS_SKINMESH_H

#include "VertexTypes.h"

namespace ZERO
{
namespace Graphics
{
	class SkinMesh
	{

	public:
		SkinMesh();
		~SkinMesh();

		void Allocate(uint32_t numVertices, uint32_t numIndices);
		void Destroy();

		BoneVertex& GetVertex(uint32_t index);
		uint32_t& GetIndex(uint32_t index);

		const BoneVertex* GetVertices() const { return mVertices; }
		const uint32_t* GetIndices() const { return mIndices; }
		uint32_t GetVertexCount() const { return mNumVertices; }
		uint32_t GetIndicesCount() const { return mNumIndices; }

		void SetVertices(BoneVertex*& vertices);
		void SetIndices(uint32_t*& indices);

	private:

		BoneVertex* mVertices;
		uint32_t* mIndices;

		uint32_t mNumVertices;
		uint32_t mNumIndices;

	};
}
}


#endif // !INCLUDED_GRAPHICS_SKINMESH_H

