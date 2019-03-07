#include "Precompiled.h"
#include "AnimationClip.h"
#include <fstream>

using namespace ZERO;
using namespace ZERO::Graphics;

AnimationClip::AnimationClip()
	: duration(0.0f)
	, ticksPerSecond(0.0f)
{}

AnimationClip::~AnimationClip()
{
	for (uint32_t i = 0; i < boneAnimations.size(); ++i)
	{
		delete boneAnimations[i];
		boneAnimations[i] = nullptr;
	}
}


void AnimationClip::GetTransform(float time, Bone* bone, Math::Matrix4& transform) const
{
	BoneAnimation* boneAnim = boneAnimations[bone->index];
	if (boneAnim)
	{
		transform = boneAnim->GetTransform(time);
	}
}

void AnimationClip::SerializeAnim()
{
	std::fstream fs;
	std::string path = "../Assets/Animations/";
	path += name;
	path += ".zeroanim";
	fs.open(path.c_str(), std::ios::binary | std::ios::out);

	//Serializing name
	char* c = new char[256];
	strcpy_s(c, 256, name.c_str());
	fs.write(c, 256);

	//Serializing duration
	SerializationUtil::MessageSerialize(duration, fs);

	//Serializing ticksPerSecond
	SerializationUtil::MessageSerialize(ticksPerSecond, fs);

	//Serializing size of the animation vector
	SerializationUtil::MessageSerialize(numberOfBonesWithAnim, fs);

	//Serializing number of bones
	SerializationUtil::MessageSerialize(totalNumberOfBones, fs);

	//Serializing bone Animation values
	for (uint32_t i = 0; i < totalNumberOfBones; ++i)
	{
		if (!boneAnimations[i])
		{
			continue;
		}
		//Serializing Bone index
		SerializationUtil::MessageSerialize(boneAnimations[i]->boneIndex, fs);

		//Serializing number of positions, rotations and scales keys
		SerializationUtil::MessageSerialize(boneAnimations[i]->GetPositionKeys().size(), fs);
		SerializationUtil::MessageSerialize(boneAnimations[i]->GetRotationKeys().size(), fs);
		SerializationUtil::MessageSerialize(boneAnimations[i]->GetScaleKeys().size(), fs);
		
		//Serializing position
		for (uint32_t j = 0; j < boneAnimations[i]->GetPositionKeys().size(); ++j)
		{
			SerializationUtil::MessageSerialize(boneAnimations[i]->GetPositionKeys()[j], fs);
		}
		//Serializing rotation
		for (uint32_t j = 0; j < boneAnimations[i]->GetRotationKeys().size(); ++j)
		{
			SerializationUtil::MessageSerialize(boneAnimations[i]->GetRotationKeys()[j], fs);
		}
		//Serializing scale
		for (uint32_t j = 0; j < boneAnimations[i]->GetScaleKeys().size(); ++j)
		{
			SerializationUtil::MessageSerialize(boneAnimations[i]->GetScaleKeys()[j], fs);
		}

	}
	
	fs.close();
}

void AnimationClip::DeserializeAnim(std::string animationName)
{
	std::string fullPath;
	fullPath += "../Assets/Animations/";
	fullPath += animationName;
	
	std::fstream fs(fullPath.c_str(), std::ios::in | std::ios::binary);

	ASSERT(!fs.fail(), "Error: File does not exist");

	//Deserializing name
	char strName[256];
	fs.read(strName, 256);
	name = strName;

	//Deserializing duration
	SerializationUtil::MessageDeserialize(duration, fs);

	//Deserializing ticks per second
	SerializationUtil::MessageDeserialize(ticksPerSecond, fs);

	//Deserializing size of the animation vector
	SerializationUtil::MessageDeserialize(numberOfBonesWithAnim, fs);

	//Deserializing number of bones
	SerializationUtil::MessageDeserialize(totalNumberOfBones, fs);

	//resizing boneAnimations array
	boneAnimations.resize(totalNumberOfBones, nullptr);

	//Deserializing bone Animation values
	for (uint32_t i = 0; i < numberOfBonesWithAnim; ++i)
	{
		BoneAnimation* newBoneAnimation = new BoneAnimation();
		
		//Deserializing Bone index
		SerializationUtil::MessageDeserialize(newBoneAnimation->boneIndex, fs);

		//Serializing number of positions, rotations and scales keys
		uint32_t nPositions, nScales, nRotations;
		SerializationUtil::MessageDeserialize(nPositions, fs);
		SerializationUtil::MessageDeserialize(nRotations, fs);
		SerializationUtil::MessageDeserialize(nScales, fs);

		newBoneAnimation->GetPositionKeys().resize(nPositions);
		newBoneAnimation->GetRotationKeys().resize(nRotations);
		newBoneAnimation->GetScaleKeys().resize(nScales);
		//Serializing position
		for (uint32_t j = 0; j < nPositions; ++j)
		{
			SerializationUtil::MessageDeserialize(newBoneAnimation->GetPositionKeys()[j], fs);
		}
		//Serializing rotation
		for (uint32_t j = 0; j < nRotations; ++j)
		{
			SerializationUtil::MessageDeserialize(newBoneAnimation->GetRotationKeys()[j], fs);
		}
		//Serializing scale
		for (uint32_t j = 0; j < nScales; ++j)
		{
			SerializationUtil::MessageDeserialize(newBoneAnimation->GetScaleKeys()[j], fs);
		}

		boneAnimations[newBoneAnimation->boneIndex] = newBoneAnimation;
	}
}

//void AnimationClip::Play(float time, Model* model)
//{
//	
//	for (uint32_t i = 0; i < model->GetBonesVector().size(); ++i)
//	{
//	Bone* bone = model->GetBonesVector()[i];
//	mBonesTransforms[i] = bone->transform;
//	while (bone->parent)
//	{
//	mBonesTransforms[i] = mBonesTransforms[i] * bone->parent->transform;
//	bone = bone->parent;
//	}
//	}
//
//	for (uint32_t i = 0; i < mBonesTransforms.size(); ++i)
//	{
//	Bone* bone = mModel->GetBonesVector()[i];
//	mBoneNode->SetTransform(i, bone->offsetTransform * mBonesTransforms[i]);
//	}
//}