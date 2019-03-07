#include "Precompiled.h"
#include "BonesTransformsNode.h"

using namespace ZERO;
using namespace ZERO::Graphics;

BonesTransformsNode::BonesTransformsNode()
	: SceneNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

BonesTransformsNode::~BonesTransformsNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void BonesTransformsNode::Initialize(uint32_t bindIndex)
{
	mConstantBuffer.Initialize();
	mTransforms.resize(100);
	mBindIndex = bindIndex;
}

//----------------------------------------------------------------------------------------------------

void BonesTransformsNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------


void BonesTransformsNode::OnRender()
{
	ConstantBuffer constants;
	for (size_t i = 0; i < mTransforms.size(); ++i)
	{
		constants.bonesTransforms[i] = Math::Transpose(mTransforms[i]);
	}
	
	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}

//----------------------------------------------------------------------------------------------------
