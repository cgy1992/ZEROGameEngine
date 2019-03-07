#ifndef INCLUDED_ENGINE_TRANSFORMCOMPONENT_H
#define INCLUDED_ENGINE_TRANSFORMCOMPONENT_H

#include "Component.h"

namespace ZERO
{
namespace Engine
{
	class TransformComponent : public Component
	{
	public:
		struct ConstantBuffer
		{
			Math::Matrix4 matWorld;
		};

		META_CLASS_DECLARE
		TransformComponent();
		~TransformComponent() override;

		void Initialize() override;
		void Render() override;
		void Terminate() override;

		Math::Vector3	Position() const { return mPosition; }
		Math::Vector3&	Position() { return mPosition; }
		void SetPosition(const Math::Matrix4& transform);

		Math::Vector3	Scale() const { return mScale; }
		Math::Vector3&	Scale() { return mScale; }
		void SetScale(const Math::Matrix4& transform);

		Math::Quaternion	Rotation() const { return mRotation; }
		Math::Quaternion&	Rotation() { return mRotation; }

		void SetRotation(const Math::Matrix4& transform);
		void SetRotation(const Math::Vector3& eulerAngles);

		void SetWorld(const Math::Matrix4& transform);
		Math::Matrix4 GetWorld();

		Math::Vector3 GetUp() const { return mUp; }
		Math::Vector3 GetForward() const { return mForward; }

	private:
		Math::Vector3 mPosition;
		Math::Vector3 mScale;
		Math::Quaternion mRotation;
		Math::Vector3 mForward;
		Math::Vector3 mUp;
		int mBindIndex{ 0 };

		ZERO::Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;
	};
}
}


#endif // #ifndef INCLUDED_ENGINE_TRANSFORMCOMPONENT_H