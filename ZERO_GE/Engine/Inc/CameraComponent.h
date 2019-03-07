#ifndef INCLUDED_ENGINE_CAMERACOMPONENT_H
#define INCLUDED_ENGINE_CAMERACOMPONENT_H

#include "Component.h"

namespace ZERO
{
namespace Engine
{
class TransformComponent;

class CameraComponent : public Component
{
public:

	struct ConstantBuffer
	{
		Math::Matrix4 matView;
		Math::Matrix4 matProjection;
		Math::Vector4 viewPosition;
		float cameraNear;
		float cameraFar;
	};

	META_CLASS_DECLARE
	CameraComponent();
	~CameraComponent() override;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
	Graphics::Camera* GetCamera() const { return mCamera.get(); }

private:
	std::string mCameraMode;
	float mFOV;
	float mNear;
	float mFar;
	bool mIsMainCamera;
	const TransformComponent* mTransformComponent;
	std::unique_ptr<Graphics::Camera> mCamera;

	int mBindIndex{ 1 };//Constant buffer register for camera

	ZERO::Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;



};
}//!namespace Engine
}//!namespace ZERO

#endif // !INCLUDED_ENGINE_CAMERACOMPONENT_H

