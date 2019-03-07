#include "Precompiled.h"
#include "RenderTargetNode.h"

using namespace ZERO;
using namespace ZERO::Graphics;

RenderTargetNode::RenderTargetNode()
	:mRenderTarget(nullptr)
	,mUseAsTexture(false)
	,mIndex(0)
{}

RenderTargetNode::~RenderTargetNode()
{
	ASSERT(mRenderTarget != nullptr, "[RenderTargetNode] Delete render Target initialized");
}



void RenderTargetNode::OnPreRender()
{
	if (false == mUseAsTexture)
	{
		mRenderTarget->BeginRender();
	}
	else
	{
		mRenderTarget->BindPS(mIndex);
	}
}

void RenderTargetNode::OnPostRender()
{
	if (false == mUseAsTexture)
	{
		mRenderTarget->EndRender();
	}
	else
	{
		mRenderTarget->UnbindPS(mIndex);
	}
}

void RenderTargetNode::Initialize(uint32_t index)
{
	mIndex = index;
}

void RenderTargetNode::Terminate()
{
	mRenderTarget->Terminate();
}

