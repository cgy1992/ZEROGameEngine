#ifndef INCLUDED_GRAPHICS_MESHNODE_H
#define INCLUDED_GRAPHICS_MESHNODE_H


//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"
#include "MeshBuffer.h"


namespace ZERO
{
namespace Graphics
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class MeshNode : public SceneNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	void SetRenderMesh(MeshBuffer* buffer) { mpMesh = buffer; }
	MeshBuffer* GetRenderMesh() const { return mpMesh; }

protected:
	virtual void OnRender();

protected:
	MeshBuffer* mpMesh;
};

}// !namespace Graphics
}// !namespace ZERO



#endif //!INCLUDED_GRAPHICS_MESHNODE_H