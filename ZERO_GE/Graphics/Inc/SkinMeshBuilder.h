#ifndef INCLUDED_GRAPHICS_SKINMESHBUILDER_H
#define INCLUDED_GRAPHICS_SKINMESHBUILDER_H

#include <Graphics\Inc\SkinMesh.h>

namespace ZERO
{
namespace Graphics
{
	class SkinMeshBuilder
	{

	public:
		SkinMeshBuilder();
		~SkinMeshBuilder();

		static void CreateCylinder(SkinMesh& mesh, uint32_t slices, uint32_t stacks, float height, float radius);
		static void CreatePlane(SkinMesh& mesh);
	};
}// namespace Graphics
}//namespace ZERO

#endif //!INCLUDED_GRAPHICS_SKINMESHBUILDER_H
