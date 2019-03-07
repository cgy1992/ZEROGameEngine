#include "Precompiled.h"
#include "MeshRendererComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "World.h"

using namespace ZERO;
using namespace ZERO::Engine;


META_DERIVED_BEGIN(MeshRendererComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mMeshName, "MeshName")
		META_FIELD(mShaderName, "ShaderName")
	META_FIELD_END
META_CLASS_END

MeshRendererComponent::MeshRendererComponent()
	: mMeshName("")
{
}

MeshRendererComponent::~MeshRendererComponent()
{
}

void MeshRendererComponent::Initialize()
{
	mSampler = std::make_unique<Graphics::Sampler>();
	mMeshBuffer = std::make_unique<Graphics::MeshBuffer>();
	/*mConstantBuffer = std::make_unique<TransformCB>();*/

	/*mTransformComponent = (TransformComponent*)GetOwner().GetComponentAt(0);*/
	mSampler->Initialize(Graphics::Sampler::Filter::Linear, Graphics::Sampler::AddressMode::Wrap);
	mMeshBuffer->Initialize(*(GetOwner().GetWorld().GetPrimitiveMeshManager()->GetResource(mMeshName)));
	/*mConstantBuffer->Initialize();*/
}

void MeshRendererComponent::Render()
{
	////Update Matrices
	//Math::Matrix4 world;
	//world =
	//{
	//	mTransformComponent->Scale().x, 0.0f, 0.0f, 0.0f,
	//	0.0f, mTransformComponent->Scale().y, 0.0f, 0.0f,
	//	0.0f, 0.0f, mTransformComponent->Scale().z, 0.0f,
	//	mTransformComponent->Position().x, mTransformComponent->Position().y, mTransformComponent->Position().z, 1.0f,

	//};

	///*TransformData data;
	//data.world = Math::Transpose(world);
	//data.view = Math::Transpose(GetOwner().GetWorld().Find("MainCamera").Get()->GetComponent<CameraComponent>()->GetCamera()->GetView());
	//data.projection = Math::Transpose(GetOwner().GetWorld().Find("MainCamera").Get()->GetComponent<CameraComponent>()->GetCamera()->GetProjection());*/
	//mConstantBuffer->Set(data);
	//mConstantBuffer->BindVS();

	GetOwner().GetWorld().GetVertexShaderManager()->GetResource(mShaderName)->Bind();
	GetOwner().GetWorld().GetPixelShaderManager()->GetResource(mShaderName)->Bind();

	mSampler->BindVS(0);
	mSampler->BindPS(0);

	mMeshBuffer->Render();
}

void MeshRendererComponent::Terminate()
{
	mSampler->Terminate();
	mMeshBuffer->Terminate();
}