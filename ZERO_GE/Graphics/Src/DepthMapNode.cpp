#include "Precompiled.h"
#include "DepthMapNode.h"

using namespace ZERO;
using namespace ZERO::Graphics;

DepthMapNode::DepthMapNode()
	: mpDepthMap(nullptr)
	, mUseAsTexture(false)
	, mIndex(0)
{}

DepthMapNode::~DepthMapNode()
{
	ASSERT(mpDepthMap != nullptr, "[RenderTargetNode] Delete render Target initialized");
}

void DepthMapNode::OnPreRender()
{
	if (false == mUseAsTexture)
	{
		mpDepthMap->BeginRender();
	}
	else
	{
		mpDepthMap->BindTexture(mIndex);
	}
}

void DepthMapNode::OnPostRender()
{
	if (false == mUseAsTexture)
	{
		mpDepthMap->EndRender();
	}
	else
	{
		mpDepthMap->UnbindTexture(mIndex);
	}
}

void DepthMapNode::Initialize(uint32_t index)
{
	mIndex = index;
}

void DepthMapNode::Terminate()
{
	mpDepthMap->Terminate();
}


