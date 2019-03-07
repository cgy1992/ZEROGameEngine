#ifndef INCLUDED_GRAPHICS_SAMPLERNODE_H
#define INCLUDED_GRAPHICS_SAMPLERNODE_H

//====================================================================================================
// Includes
//====================================================================================================
#include "SceneNode.h"
#include "Sampler.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace ZERO
{
namespace Graphics
{
	class SamplerNode : public SceneNode
	{
	public:
		SamplerNode();
		virtual ~SamplerNode();

		void Initialize(Sampler::Filter filter, Sampler::AddressMode address);
		void Initialize(Sampler::Filter filter, Sampler::AddressMode address, uint32_t index);
		void Terminate();

	protected:
		virtual void OnRender();

	protected:
		Sampler mpSampler;
		uint32_t mIndex;
	};
}// !namespace Graphics
}//! namespace ZERO


#endif //!INCLUDED_GRAPHICS_SAMPLERNODE_H