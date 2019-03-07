#ifndef INCLUDED_ENGINE_MESHRENDERERCOMPONENT_H
#define INCLUDED_ENGINE_MESHRENDERERCOMPONENT_H

#include "Component.h"

namespace ZERO
{
namespace Engine
{
class TransformComponent;
class MeshRendererComponent : public Component
{
public:
	META_CLASS_DECLARE
	MeshRendererComponent();
	~MeshRendererComponent() override;

	void Initialize() override;
	void Render() override;
	void Terminate() override;


private:
	struct TransformData
	{
		ZERO::Math::Matrix4 world;
		ZERO::Math::Matrix4 view;
		ZERO::Math::Matrix4 projection;
	};

	typedef ZERO::Graphics::TypedConstantBuffer<TransformData> TransformCB;

	std::string mMeshName;
	std::string mShaderName;
	std::unique_ptr<Graphics::MeshBuffer> mMeshBuffer;
	std::unique_ptr<TransformCB> mConstantBuffer;
	std::unique_ptr<Graphics::Sampler> mSampler;
	const TransformComponent* mTransformComponent;
};
}//!namespace Engine
}//!namespace ZERO

#endif // !INCLUDED_ENGINE_TEXTURECOMPONENT_H


