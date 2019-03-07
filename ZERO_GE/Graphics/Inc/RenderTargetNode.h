#ifndef INCLUDED_GRAPHICS_RENDERTARGETNODE_H
#define INCLUDED_GRAPHICS_RENDERTARGETNODE_H

#include "SceneNode.h"
#include "RenderTarget.h"
#include "Types.h"

namespace ZERO
{
namespace Graphics
{
class RenderTargetNode : public SceneNode
{
public:
	RenderTargetNode();
	~RenderTargetNode();


	void OnPreRender()			   override;
	void OnPostRender()			   override;

	void Initialize(uint32_t index);
	void Terminate();

	void SetRenderTarget(RenderTarget* rt) { mRenderTarget = rt; }

	void SetHasTexture(bool hastexture) { mUseAsTexture = hastexture; }

protected:
	RenderTarget* mRenderTarget;
	bool mUseAsTexture;
	uint32_t mIndex;



};
}
}


#endif // !INCLUDED_GRAPHICS_RENDERTARGETNODE_H

