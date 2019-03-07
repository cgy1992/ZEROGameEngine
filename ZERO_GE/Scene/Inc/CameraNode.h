#ifndef INCLUDED_SCENE_CAMERANODE_H
#define INCLUDED_SCENE_CAMERANODE_H


#include "SceneNode.h"
#include <Graphics/Inc/Graphics.h>


namespace ZERO
{
namespace SCENE
{

class CameraNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Matrix4 matView;
		Math::Matrix4 matProjection;
		Math::Vector3 viewPosition;
	};

	CameraNode();
	virtual ~CameraNode();

	void Initialize();
	void Terminate();

	void SetCamera(Graphics::Camera* camera) { mpCamera = camera; }
	Graphics::Camera* GetCamera() { return mpCamera; }

protected:
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender();

protected:
	ZERO::Graphics::TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Graphics::Camera* mpCamera;
};
}
}


#endif // #ifndef INCLUDED_SIEGE_CAMERANODE_H