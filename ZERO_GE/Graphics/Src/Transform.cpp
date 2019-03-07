#include "Precompiled.h"
#include "Transform.h"


using namespace ZERO;
using namespace ZERO::Graphics;

Transform::Transform()
	:mScale(Math::Vector3(1.0f, 1.0f, 1.0f))
{}

Transform::~Transform()
{}

void Transform::SetRotation(const Math::Vector3& eulerAngles)
{
	mRotation = Math::EulerToQuaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Math::Matrix4 Transform::GetWorld()
{
	Math::Matrix4 world;
	
	Math::Matrix4 rotMatrix = Math::QuaternionToMatrix(mRotation);

	world = Math::Matrix4::Scaling(mScale)
		* rotMatrix
		* Math::Matrix4::Translation(mPosition);

	return world;
}

void Transform::SetWorld(const Math::Matrix4& transform)
{
	mPosition = { transform._41, transform._42, transform._43 };
	mScale = {
		Math::Magnitude({ transform._11, transform._12, transform._13 }),
		Math::Magnitude({ transform._21, transform._22, transform._23 }),
		Math::Magnitude({ transform._31, transform._32, transform._33 }) };
	auto unscaled = Math::Inverse(Math::Matrix4::Scaling(mScale)) * transform;
	mRotation = Math::QuaternionFromMatrix(unscaled);
}

void Transform::SetScale(const Math::Matrix4& transform)
{
	mScale = {	Math::Magnitude({ transform._11, transform._12, transform._13 }),
				Math::Magnitude({ transform._21, transform._22, transform._23 }),
				Math::Magnitude({ transform._31, transform._32, transform._33 }) };
}

void Transform::SetRotation(const Math::Matrix4& transform)
{
	mRotation = Math::QuaternionFromMatrix(transform);
}

void Transform::SetPosition(const Math::Matrix4& transform) 
{ 
	mPosition = { transform._41, transform._42, transform._43 }; 
}