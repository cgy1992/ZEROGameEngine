#ifndef INCLUDED_GRAPHICS_CAMERA_H
#define INCLUDED_GRAPHICS_CAMERA_H

namespace ZERO
{
namespace Graphics
{
class Camera
{
public:
	Camera();
	~Camera();

	//Getters
	Math::Vector3 GetPosition() const	{ return mPosition; }
	Math::Vector3 GetDirection() const	{ return mDirection; }
	void SetDirection(Math::Vector3 direction) { mDirection = direction; }

	//Math::Vector3 GetRight() const		{ return mRight; }
	Math::Vector3 GetUp() const			{ return mUp; }
	Math::Vector3 GetRight() const;

	float GetFOV() const				{ return mFOV; }
	float GetNearPlane() const			{ return mNearPlane; }
	float GetFarPlane() const			{ return mFarPlane; }
	float GetHeight() const				{ return mHeight; }
	float GetWidth() const				{ return mWidth; }

	Math::Matrix4 GetView() const		{ return mView; }
	Math::Matrix4 GetProjection() const { return mProjection; }


	//Setters
	void SetPosition(Math::Vector3 pos) { mPosition = pos; }
	//Set Frustum
	void SetLens(float fov, float width, float height, float nearPlane, float farPlane);
	void SetLens(float fov, float aspect, float nearPlane, float farPlane);

	void LookAt(const Math::Vector3& targetPosition);

	//Strafe and walk
	void Strafe(float d);
	void Walk(float d);
	void Rise(float d);
	
	//Rotate the camera
	void Yaw(float degree); //RotateY
	void Pitch(float degree);
	void Roll(float degree);
	

	//Features TODO
	void Dollyzoom(float dz, float dRadians);


	void UpdateViewMatrix();
	void CreatePerspectiveMatrix(float aspect = 0);
	void CreateOrthographicMatrix(float width = 0, float height = 0);

	

private:

	Math::Vector3 mPosition;
	Math::Vector3 mDirection;
	Math::Vector3 mUp;

	float mFOV;
	float mNearPlane;
	float mFarPlane;
	float mHeight;
	float mWidth;

	Math::Matrix4 mView;
	Math::Matrix4 mProjection;
};


}//namespace Graphics
}//Namespace ZERO


#endif
