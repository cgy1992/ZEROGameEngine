#include "Precompiled.h"
#include "Animation.h"

using namespace ZERO;
using namespace ZERO::Graphics;

Animation::Animation()
	:mLoop(true)
{}

Animation::~Animation()
{}



Math::Matrix4 Animation::GetTransform(float time)
{
	if (time == 0.0f)
	{
		currentPositionIndex = 0;
		currentRotationIndex = 0;
		currentScaleIndex = 0;
	}
	uint32_t indexPos = 0;
	bool lastPosFrame = false;
	uint32_t indexRot = 0;
	bool lastRotFrame = false;
	uint32_t indexScale = 0;
	bool lastScaleFrame = false;

	Math::Vector3 position;
	Math::Quaternion rotation;
	Math::Vector3 scale;

	for (uint32_t i = currentPositionIndex; i < mPositionKeyframes.size(); ++i)
	{
		if (time >= mPositionKeyframes[mPositionKeyframes.size() - 1].timer)
		{
			//Last position
			indexPos = static_cast<uint32_t>(mPositionKeyframes.size()) - 1;
			currentPositionIndex = indexPos;
			lastPosFrame = true;
			break;
		}
		if (time >= mPositionKeyframes[i].timer && time < mPositionKeyframes[i + 1].timer)
		{
			indexPos = i;
			currentPositionIndex = indexPos;
			break;
		}
	}
	for (uint32_t j = currentRotationIndex; j < mRotationKeyframes.size(); ++j)
	{
		if (time >= mRotationKeyframes[mRotationKeyframes.size() - 1].timer)
		{
			//Last position
			indexRot = static_cast<uint32_t>(mRotationKeyframes.size()) - 1;
			currentRotationIndex = indexRot;
			lastRotFrame = true;
			break;
		}
		if (time >= mRotationKeyframes[j].timer && time < mRotationKeyframes[j + 1].timer)
		{
			indexRot = j;
			currentRotationIndex = indexRot;
			break;
		}
	}
	for (uint32_t k = currentScaleIndex; k < mScaleKeyframes.size(); ++k)
	{
		if (time >= mScaleKeyframes[mScaleKeyframes.size() - 1].timer)
		{
			//Last position
			indexScale = static_cast<uint32_t>(mScaleKeyframes.size()) - 1;
			currentScaleIndex = indexScale;
			lastScaleFrame = true;
			break;
		}
		if (time >= mScaleKeyframes[k].timer && time < mScaleKeyframes[k + 1].timer)
		{
			indexScale = k;
			currentScaleIndex = indexScale;
			break;
		}
	}

	if (lastPosFrame == true)
	{
		position = mPositionKeyframes[indexPos].GetValue();
		currentPositionIndex = 0;
	}
	else
	{
		float totalTimeBetweenFrames = mPositionKeyframes[indexPos + 1].timer - mPositionKeyframes[indexPos].timer;
		float currentTimeBetweenFrames = time - mPositionKeyframes[indexPos].timer;
		float lerpTime = currentTimeBetweenFrames / totalTimeBetweenFrames;
		position = Math::Lerp(	mPositionKeyframes[indexPos].GetValue(), 
										mPositionKeyframes[indexPos + 1].GetValue(), 
										lerpTime);
	}

	if (lastRotFrame == true)
	{
		rotation = mRotationKeyframes[indexRot].GetValue();
		currentRotationIndex = 0;
	}
	else
	{
		float totalTimeBetweenFrames = mRotationKeyframes[indexRot + 1].timer - mRotationKeyframes[indexRot].timer;
		float currentTimeBetweenFrames = time - mRotationKeyframes[indexRot].timer;
		float slerpTime = currentTimeBetweenFrames / totalTimeBetweenFrames;
		rotation = Math::Slerp(mRotationKeyframes[indexRot].GetValue(), mRotationKeyframes[indexRot + 1].GetValue(), slerpTime);
	}

	if (lastScaleFrame == true)
	{
		scale = mScaleKeyframes[indexScale].GetValue();
		currentScaleIndex = 0;
	}
	else
	{
		float totalTimeBetweenFrames = mScaleKeyframes[indexScale + 1].timer - mScaleKeyframes[indexScale].timer;
		float currentTimeBetweenFrames = time - mScaleKeyframes[indexScale].timer;
		float lerpTime = currentTimeBetweenFrames / totalTimeBetweenFrames;
		scale = Math::Lerp(		mScaleKeyframes[indexScale].GetValue(), 
								mScaleKeyframes[indexScale + 1].GetValue(),
								lerpTime );
	}

	Math::Matrix4 rotMatrix = Math::QuaternionToMatrix(rotation);
	Math::Matrix4 transformMatrix = Math::Matrix4::Scaling(scale)
								  * rotMatrix
								  * Math::Matrix4::Translation(position);

	return transformMatrix;
}

void Animation::AddPositionKey(Keyframe<Math::Vector3> pos)
{
	if (isKeyVector3Set(pos.timer, mPositionKeyframes))
	{
		std::vector<Keyframe<Math::Vector3>>::iterator it = mPositionKeyframes.begin();
		for (; it != mPositionKeyframes.end(); it++)
		{
			if (it->timer == pos.timer)
			{
				it->SetValue(pos.GetValue());
				return;
			}
		}
	}

	mPositionKeyframes.push_back(pos);
}

void Animation::AddRotationKey(Keyframe<Math::Quaternion> rot)
{
	if (isKeyVector3Set(rot.timer, mRotationKeyframes))
	{
		std::vector<Keyframe<Math::Quaternion>>::iterator it = mRotationKeyframes.begin();
		for (; it != mRotationKeyframes.end(); it++)
		{
			if (it->timer == rot.timer)
			{
				it->SetValue(rot.GetValue());
				return;
			}
		}
	}
	mRotationKeyframes.push_back(rot);
}

void Animation::AddScaleKey(Keyframe<Math::Vector3> scale)
{
	if (isKeyVector3Set(scale.timer, mScaleKeyframes))
	{
		std::vector<Keyframe<Math::Vector3>>::iterator it = mScaleKeyframes.begin();
		for (; it != mScaleKeyframes.end(); it++)
		{
			if (it->timer == scale.timer)
			{
				it->SetValue(scale.GetValue());
				return;
			}
		}
	}
	mScaleKeyframes.push_back(scale);
}


template<typename T>
bool Animation::isKeyVector3Set(float time, std::vector<Keyframe<T>> vec)
{
	std::vector<Keyframe<T>>::iterator it;

	for (it = vec.begin(); it != vec.end(); it++)
	{
		if (it->timer == time)
		{
			return true;
		}
	}
	return false;
}

void Animation::SortFrames()
{
	auto lessLambdaComp = [](const auto& lhs, const auto& rhs){ return lhs.timer < rhs.timer; };

	std::sort(mPositionKeyframes.begin(), mPositionKeyframes.end(), lessLambdaComp);
	std::sort(mRotationKeyframes.begin(), mRotationKeyframes.end(), lessLambdaComp);
	std::sort(mRotationKeyframes.begin(), mRotationKeyframes.end(), lessLambdaComp);
}