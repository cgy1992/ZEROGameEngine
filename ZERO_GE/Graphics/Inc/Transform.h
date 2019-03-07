#ifndef INCLUDED_GRAPHICS_TRANSFORM
#define INCLUDED_GRAPHICS_TRANSFORM

namespace ZERO
{
namespace Graphics
{
class Transform
{
public:
	Transform();
	~Transform();

	Math::Vector3	Position() const { return mPosition; }
	Math::Vector3&	Position() { return mPosition; }
	void SetPosition(const Math::Matrix4& transform);

	Math::Vector3	Scale() const { return mScale; }
	Math::Vector3&	Scale() { return mScale; }
	void SetScale(const Math::Matrix4& transform);

	Math::Quaternion	Rotation() const { return mRotation; }
	Math::Quaternion&	Rotation() { return mRotation; }

	void SetRotation(const Math::Matrix4& transform);
	void SetRotation(const Math::Vector3& transform);

	void SetWorld(const Math::Matrix4& transform);
	Math::Matrix4 GetWorld();


private:
	Math::Vector3 mPosition;
	Math::Quaternion mRotation;
	Math::Vector3 mScale;
	Math::Matrix4 temp;
};

}// !namespace Graphics
}// !namespace ZERO

#endif // !INCLUDED_GRAPHICS_TRANSFORM

