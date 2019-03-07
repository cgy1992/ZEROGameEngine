#ifndef INCLUDED_GRAPHICS_GRAPHICSUTIL_H
#define INCLUDED_GRAPHICS_GRAPHICSUTIL_H

#include "Mesh.h"
#include "SkinMesh.h"

namespace ZERO
{
namespace Graphics
{
class GraphicsUtil
{
public:
	static void ComputeNormals(Mesh& mesh);
	static void ComputeNormals(SkinMesh& mesh);
};
}
}



#endif // !INCLUDED_GRAPHICS_GRAPHICSUTIL_H
