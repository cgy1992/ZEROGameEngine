#ifndef INCLUDED_SCENE_MESHNODE_H
#define INCLUDED_SCENE_MESHNODE_H


//====================================================================================================
// Includes
//====================================================================================================
#include <Graphics/Inc/Graphics.h>
#include "SceneNode.h"

namespace ZERO
{
namespace SCENE
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class MeshNode : public SceneNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	void SetRenderMesh(Graphics::MeshBuffer* buffer) { mpMesh = buffer; }
	Graphics::MeshBuffer* GetRenderMesh() const { return mpMesh; }

protected:
	virtual void OnRender();

protected:
	Graphics::MeshBuffer * mpMesh;
};

}// !namespace SCENE
}// !namespace ZERO



#endif // #ifndef INCLUDED_SIEGE_SHADERNODE_H