#ifndef INCLUDED_GRAPHICS_MESHBUILDER_H
#define INCLUDED_GRAPHICS_MESHBUILDER_H

#include <Graphics\Inc\Mesh.h>


namespace ZERO
{
namespace Graphics
{
class MeshBuilder
{

public:
	MeshBuilder();
	~MeshBuilder();

	static void CreateCube(Mesh& mesh);
	static void CreateSkyBox(Mesh& mesh);
	static void CreateSphere(Mesh& mesh, uint32_t rings, uint32_t slices);
	static void CreateSkySphere(Mesh& mesh, uint32_t stacks, uint32_t slices);
	static void CreatePlane(Mesh& mesh);
	static void CreateCylinder(Mesh& mesh, uint32_t slices, uint32_t stacks);
	static void CreateCustomCylinder(Mesh& mesh, float bottomRadius, float topRadius, float height, uint32_t slices, uint32_t stacks);
};
}// namespace Graphics
}//namespace ZERO

#endif // !INCLUDED_GRAPHICS_MESHBUILDER_H

