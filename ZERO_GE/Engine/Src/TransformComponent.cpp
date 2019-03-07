#include "Precompiled.h"
#include "TransformComponent.h"

using namespace ZERO;
using namespace ZERO::Engine;

META_DERIVED_BEGIN(TransformComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mPosition, "Position")
		META_FIELD(mRotation, "Quaternion")
		META_FIELD(mScale, "Scale")
		META_FIELD(mUp, "Up")
		META_FIELD(mForward, "Heading")
		META_FIELD(mBindIndex, "TransformBindIndex")
	META_FIELD_END
META_CLASS_END

TransformComponent::TransformComponent()
	: mForward(Math::Vector3::ZAxis())
	, mUp(Math::Vector3::YAxis())
	, mScale(Math::Vector3::One())
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize()
{
	mConstantBuffer.Initialize();
	mBindIndex = mBindIndex;
}

void TransformComponent::Render()
{
	ConstantBuffer constants;
	constants.matWorld = Math::Transpose(GetWorld());
	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}

void TransformComponent::Terminate()
{
	mConstantBuffer.Terminate();
}

void TransformComponent::SetRotation(const Math::Vector3& eulerAngles)
{
	mRotation = Math::EulerToQuaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Math::Matrix4 TransformComponent::GetWorld()
{
	Math::Matrix4 world;

	Math::Matrix4 rotMatrix = Math::QuaternionToMatrix(mRotation);

	world = Math::Matrix4::Scaling(mScale)
		* rotMatrix
		* Math::Matrix4::Translation(mPosition);

	return world;
}

void TransformComponent::SetWorld(const Math::Matrix4& transform)
{
	mPosition = { transform._41, transform._42, transform._43 };
	mScale = {
		Math::Magnitude({ transform._11, transform._12, transform._13 }),
		Math::Magnitude({ transform._21, transform._22, transform._23 }),
		Math::Magnitude({ transform._31, transform._32, transform._33 }) };
	auto unscaled = Math::Inverse(Math::Matrix4::Scaling(mScale)) * transform;
	mRotation = Math::QuaternionFromMatrix(unscaled);
}

void TransformComponent::SetScale(const Math::Matrix4& transform)
{
	mScale = { Math::Magnitude({ transform._11, transform._12, transform._13 }),
				Math::Magnitude({ transform._21, transform._22, transform._23 }),
				Math::Magnitude({ transform._31, transform._32, transform._33 }) };
}

void TransformComponent::SetRotation(const Math::Matrix4& transform)
{
	mRotation = Math::QuaternionFromMatrix(transform);
}

void TransformComponent::SetPosition(const Math::Matrix4& transform)
{
	mPosition = { transform._41, transform._42, transform._43 };
}