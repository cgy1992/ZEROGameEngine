#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace ZERO;
using namespace ZERO::Graphics;

AnimationBuilder::AnimationBuilder()
	: mTime(0.0f)
{}

AnimationBuilder::~AnimationBuilder()
{}

AnimationBuilder& AnimationBuilder::AddPositionKey(Math::Vector3 position, float time)
{
	Keyframe<Math::Vector3> keyPos;
	keyPos.timer = time;
	keyPos.SetValue(position);

	mAnimation.AddPositionKey(keyPos);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(Math::Quaternion rotation, float time)
{
	Keyframe<Math::Quaternion> keyRot;
	keyRot.timer = time;
	keyRot.SetValue(rotation);

	mAnimation.AddRotationKey(keyRot);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(Math::Vector3 scale, float time)
{
	Keyframe<Math::Vector3> keyScale;
	keyScale.timer = time;
	keyScale.SetValue(scale);

	mAnimation.AddScaleKey(keyScale);
	return *this;
}

AnimationBuilder& AnimationBuilder::SetInitialState(const Transform& transform)
{
	float initialTime = 0.0f;
	Keyframe<Math::Vector3> keyPos;
	keyPos.timer = initialTime;
	keyPos.SetValue(transform.Position());

	Keyframe<Math::Quaternion> keyRot;
	keyRot.timer = initialTime;
	keyRot.SetValue(transform.Rotation());

	Keyframe<Math::Vector3> keyScale;
	keyScale.timer = initialTime;
	keyScale.SetValue(transform.Scale());

	mAnimation.AddPositionKey(keyPos);
	mAnimation.AddRotationKey(keyRot);
	mAnimation.AddScaleKey(keyScale);

	return *this;
}

AnimationBuilder& AnimationBuilder::Build()
{
	mAnimation.SortFrames();

	return *this;
}


AnimationBuilder& AnimationBuilder::Loop(bool loopState)
{
	mAnimation.SetLoop(loopState);
	return *this;
}