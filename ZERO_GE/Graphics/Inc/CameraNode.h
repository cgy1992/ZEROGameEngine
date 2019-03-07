#ifndef INCLUDED_SCENE_CAMERANODE_H
#define INCLUDED_SCENE_CAMERANODE_H

#include "SceneNode.h"
#include "Camera.h"
#include "ConstantBuffer.h"

namespace ZERO
{
namespace Graphics
{

class CameraNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Matrix4 matView[2];
		Math::Matrix4 matProjection[2];
		Math::Vector4 viewPosition[2];
		float cameraNear[2];
		float cameraFar[2];
	};

	CameraNode();
	virtual ~CameraNode();

	void Initialize(uint32_t bindIndex = 1);
	void Terminate();

	void SetCamera(Camera* camera, uint32_t index = 0) { mCameras[index] = camera; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	std::array<Camera*, 2> mCameras;
	uint32_t mBindIndex;
};
}
}


#endif //INCLUDED_SCENE_CAMERANODE_H