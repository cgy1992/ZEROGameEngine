#ifndef INCLUDED_SIEGE_SAMPLERNODE_H
#define INCLUDED_SIEGE_SAMPLERNODE_H

//====================================================================================================
// Includes
//====================================================================================================

#include <Graphics/Inc/Graphics.h>
#include "SceneNode.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace ZERO
{
namespace SCENE
{
	class SamplerNode : public SceneNode
	{
	public:
		SamplerNode();
		virtual ~SamplerNode();

		void Initialize(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode address);
		void Terminate();

	protected:
		virtual void OnRender();

	protected:
		Graphics::Sampler mpSampler;
	};
}// !namespace SCENE
}//! namespace ZERO


#endif // #ifndef INCLUDED_SIEGE_SAMPLERNODE_H