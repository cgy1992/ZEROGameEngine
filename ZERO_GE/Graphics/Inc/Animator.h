#ifndef INCLUDED_GRAPHICS_ANIMATOR_H
#define INCLUDED_GRAPHICS_ANIMATOR_H

#include "Model.h"
#include "AnimationController.h"

namespace ZERO
{
namespace Graphics
{

class Animator
{
public:
	Animator();
	void Initialize(Model* model, AnimationController* controller);
	void Play(float deltaTime);
private:
	Model * mModel{ nullptr };
	AnimationController* mController{ nullptr };
	float mElapsedTime;
	float mBlendTime;

};

}//!namespace Graphics
}//!namespace ZERO
#endif // !1
