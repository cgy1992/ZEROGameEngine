
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SamplerNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::SCENE;

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

void SamplerNode::Initialize(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address)
{
	// Create the sample state
	mpSampler.Initialize(filter, address);
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::Terminate()
{
	mpSampler.Terminate();
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::OnRender()
{
	mpSampler.BindVS(0);
	mpSampler.BindPS(0);
}