
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SamplerNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

SamplerNode::SamplerNode()
	: SceneNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SamplerNode::~SamplerNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::Initialize(Sampler::Filter filter, Sampler::AddressMode address, uint32_t index)
{
	// Create the sample state
	mpSampler.Initialize(filter, address);
	mIndex = index;
}

void SamplerNode::Initialize(Sampler::Filter filter, Sampler::AddressMode address)
{
	// Create the sample state
	mpSampler.Initialize(filter, address);
	mIndex = 0;
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::Terminate()
{
	mpSampler.Terminate();
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::OnRender()
{
	mpSampler.BindPS(mIndex);
}