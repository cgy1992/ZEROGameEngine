#include "Precompiled.h"
#include "Camera.h"
#include "GraphicsSystem.h"

using namespace ZERO;
using namespace ZERO::Graphics;


Camera::Camera()
	:mPosition{ 0.0f, 0.0f, 0.0f }
	, mDirection{ 0.0f, 0.0f, 1.0f }
	//, mRight()
	, mUp{0.0f, 1.0f, 0.0f}
	, mFOV(0.0f)
	, mNearPlane(0.0f)
	, mFarPlane(0.0f)
	, mView()
	, mProjection()
{}

Camera::~Camera()
{}

void Camera::SetLens(float fov, float width, float height, float nearPlane, float farPlane)
{
	mFOV = fov;
	mWidth = width;
	mHeight = height;
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
}

void Camera::SetLens(float fov, float aspect, float nearPlane, float farPlane)
{
	mFOV = fov;
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
}

void Camera::LookAt(const Math::Vector3 & targetPosition)
{
	Math::Vector3 zAxis = Math::Normalize(targetPosition - mPosition);

	mDirection = zAxis;
}

void Camera::Strafe(float d)
{
	mPosition += GetRight() * d;
}

void Camera::Walk(float d)
{
	mPosition += mDirection * d;
}

void Camera::Rise(float d)
{
	mPosition += mUp * d;
}

void Camera::Yaw(float degree)
{
	float radians = Math::kDegToRad * degree;
	Math::Matrix4 Rotation = Math::Matrix4::RotationY(radians);
	mDirection = Math::TransformNormal(mDirection, Rotation);
	mUp = Math::TransformNormal(mUp, Rotation);
}

void Camera::Pitch(float degree)
{
	float radians = Math::kDegToRad * degree;

	Math::Matrix4 Rotation = Math::MatrixRotationAxis(GetRight(), radians);
	mDirection = Math::TransformNormal(mDirection, Rotation);
	mUp = Math::TransformNormal(mUp, Rotation);
}

void Camera::Roll(float degree)
{
	float radians = Math::kDegToRad * degree;
	Math::Matrix4 Rotation = Math::MatrixRotationAxis(mDirection, radians);
	mUp = Math::TransformNormal(mUp, Rotation);
}

void Camera::UpdateViewMatrix()
{

	Math::Vector3 right = GetRight();

	//Orthonormalize up
	mUp = Math::Normalize(Math::Cross(mDirection, right));
	
	//Calculate the new right for the new up
	right = Math::Cross(mUp, mDirection);

	float x = -Math::Dot(mPosition, right);
	float y = -Math::Dot(mPosition, mUp);
	float z = -Math::Dot(mPosition, mDirection);

	mView =
	{
		right.x, mUp.x, mDirection.x, 0.0f,
		right.y, mUp.y, mDirection.y, 0.0f,
		right.z, mUp.z, mDirection.z, 0.0f,
			  x,	 y,			   z, 1.0f,
	};

}

void Camera::CreatePerspectiveMatrix(float aspect)
{
	float h, w, Q;
	float aspectRatio = aspect;

	if (aspect == 0)
	{
		aspectRatio = ZERO::Graphics::GraphicsSystem::Get()->GetAspectRatio();
	}

	h = 1.0f / tanf(mFOV * 0.5f);
	w = h / aspectRatio;

	Q = mFarPlane / (mFarPlane - mNearPlane);

	mProjection =
	{
		w,		0.0f,		0.0f,		0.0f,
		0.0f,		h,		0.0f,		0.0f,
		0.0f,	0.0f,		Q,			1.0f,
		0.0f,	0.0f, -Q * mNearPlane,	0.0f
	};
}

void Camera::CreateOrthographicMatrix(float w, float h)
{
	float width;
	float height;
	if (w == 0 || h == 0)
	{
		width = static_cast<float>(GraphicsSystem::Get()->GetWidth());
		height = static_cast<float>(GraphicsSystem::Get()->GetHeight());
	}
	else
	{
		width = w;
		height = h;
	}

	mProjection =
	{
		2.0f / width,	0.0f,				0.0f,						0.0f,
		0.0f,	2.0f / height,				0.0f,						0.0f,
		0.0f,	0.0f,	1.0f / (mFarPlane - mNearPlane),			0.0f,
		0.0f,	0.0f,	-mNearPlane / (mFarPlane - mNearPlane),		1.0f
	};

}

Math::Vector3 Camera::GetRight() const
{
	Math::Vector3 right = Math::Normalize(Math::Cross(mUp, mDirection));
	return right;
}

void Camera::Dollyzoom(float dz, float degrees)
{
	float radians = Math::kDegToRad * degrees;

	mFOV += degrees;
	mPosition += mDirection * dz;

	CreatePerspectiveMatrix();
}

