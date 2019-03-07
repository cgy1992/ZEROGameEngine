#include "Precompiled.h"

#include "RasterizerStateNode.h"
#include "RasterizerState.h"

using namespace ZERO;
using namespace ZERO::Graphics;

RasterizerStateNode::RasterizerStateNode()
	:mRasterizerState(nullptr)
{}



void RasterizerStateNode::OnPreRender()
{
	mRasterizerState->Set();
}

void RasterizerStateNode::OnPostRender()
{
	mRasterizerState->Clear();
}