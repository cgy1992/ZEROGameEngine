#ifndef INCLUDED_GRAPHICS_RASTERIZERSTATENODE_H
#define INCLUDED_GRAPHICS_RASTERIZERSTATENODE_H

#include "SceneNode.h"
#include "RasterizerState.h"


namespace ZERO
{
namespace Graphics
{
class RasterizerStateNode : public SceneNode
{
public:

	RasterizerStateNode();
	~RasterizerStateNode() {}
	void SetRenderState(RasterizerState* rasterizerState) { mRasterizerState = rasterizerState; }

protected:
	virtual void OnPreRender();
	virtual void OnPostRender();

private:
	RasterizerState* mRasterizerState;
};
}
}


#endif // !INCLUDED_GRAPHICS_RASTERIZERSTATENODE_H

