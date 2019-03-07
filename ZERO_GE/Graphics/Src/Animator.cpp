#include "Precompiled.h"
#include "Animator.h"

using namespace ZERO;
using namespace ZERO::Graphics;

Animator::Animator(){}

void Animator::Initialize(Model* model, AnimationController* controller)
{
	mModel = model;
	mController = controller;
}

void Animator::Play(float deltaTime)
{
	mElapsedTime += deltaTime;
}