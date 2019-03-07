#include "Precompiled.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "World.h"

using namespace ZERO;
using namespace ZERO::Engine;


META_DERIVED_BEGIN(CameraComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mCameraMode, "CameraMode")
		META_FIELD(mFOV, "FOV")
		META_FIELD(mNear, "NearPlane")
		META_FIELD(mFar, "FarPlane")
		META_FIELD(mBindIndex, "CameraBindIndex")
		META_FIELD(mIsMainCamera, "IsMain")
	META_FIELD_END
META_CLASS_END

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Initialize()
{
	mConstantBuffer.Initialize();
	mCamera = std::make_unique<Graphics::Camera>();
	mTransformComponent = (TransformComponent*)GetOwner().GetComponentAt(0);
	mCamera->SetLens(mFOV, 0, mNear, mFar);
	mCamera->SetPosition(mTransformComponent->Position());
	if (strcmp(mCameraMode.c_str(), "Perspective") == 0)
	{
		mCamera->CreatePerspectiveMatrix();
	}
	else
	{
		mCamera->CreateOrthographicMatrix();
	}
}

void CameraComponent::Render()
{
	ConstantBuffer constants;

	constants.matView = Math::Transpose(mCamera->GetView());
	constants.matProjection = Math::Transpose(mCamera->GetProjection());
	constants.viewPosition = { mCamera->GetPosition(), 1.0f };
	constants.cameraNear = mCamera->GetNearPlane();
	constants.cameraFar = mCamera->GetFarPlane();

	Graphics::SimpleDraw::AddCube(0.1f, mCamera->GetPosition(), Math::Vector4::Yellow());

	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(mBindIndex);
	mConstantBuffer.BindPS(mBindIndex);
}

void CameraComponent::Update(float deltaTime)
{
	mCamera->UpdateViewMatrix();

	if (mIsMainCamera)
	{
		Input::InputSystem* is = Input::InputSystem::Get();
		float velocity = 10.0f;
		float rotVelocity = 10.0f;

		if (is->IsKeyDown(Input::KeyCode::LSHIFT))
		{
			velocity = 100.0f;
		}

		if (is->IsKeyDown(Input::KeyCode::W))
		{
			mCamera->Walk(velocity * deltaTime);
		}

		if (is->IsKeyDown(Input::KeyCode::S))
		{
			mCamera->Walk(-velocity * deltaTime);
		}

		if (is->IsKeyDown(Input::KeyCode::D))
		{
			mCamera->Strafe(velocity * deltaTime);
		}
		if (is->IsKeyDown(Input::KeyCode::A))
		{
			mCamera->Strafe(-velocity * deltaTime);
		}

		if (is->IsMouseDown(Input::MouseButton::RBUTTON))
		{
			mCamera->Pitch(is->GetMouseMoveY() * rotVelocity * deltaTime);
			mCamera->Yaw(is->GetMouseMoveX() * rotVelocity * deltaTime);
		}

		if (is->IsMouseDown(Input::MouseButton::MBUTTON))
		{
			mCamera->Rise(is->GetMouseMoveY() * deltaTime);
			mCamera->Strafe(is->GetMouseMoveX() * deltaTime);
		}
	}
}

void CameraComponent::Terminate()
{
	mConstantBuffer.Terminate();
}