#include "Precompiled.h"
#include "AnimationController.h"

using namespace ZERO;
using namespace ZERO::Graphics;

AnimationController::AnimationController()
{
	CreateState("EntryState", nullptr);
	SetCurrentState("EntryState");
}

AnimationController::~AnimationController()
{
	if (states.size() > 0)
	{
		for(uint32_t i = 0; i < states.size(); ++i)
		{
			SafeDelete(states[i]);
		}
	}
}

void AnimationController::AddTrigger(std::string name, bool currentValue)
{
	BoolTrigger newTrigger;
	newTrigger.trigger = currentValue;
	boolTriggers.try_emplace(name, newTrigger);
}

void AnimationController::AddTrigger(std::string name, int currentValue, TriggerConditional currentConditionalEnum)
{
	IntTrigger newTrigger;
	newTrigger.trigger = currentValue;
	newTrigger.conditionalEnum = currentConditionalEnum;
	intTriggers.try_emplace(name, newTrigger);
}

void AnimationController::AddTrigger(std::string name, float currentValue, TriggerConditional currentConditionalEnum)
{
	FloatTrigger newTrigger;
	newTrigger.trigger = currentValue;
	newTrigger.conditionalEnum = currentConditionalEnum;
	floatTriggers.try_emplace(name, newTrigger);
}

void AnimationController::SetTrigger(std::string triggerName)
{
	auto it = boolTriggers.find(triggerName);
	ASSERT(it != boolTriggers.end(), "Error: trigger name could not be found");

	if (it->second.trigger)
	{
		it->second.trigger = false;
		return;
	}
	it->second.trigger = true;
}

void AnimationController::SetTriggerValue(std::string triggerName, int value)
{
	auto it = intTriggers.find(triggerName);
	ASSERT(it != intTriggers.end(), "Error: trigger name could not be found");
	it->second.trigger = value;
}

void AnimationController::SetTriggerValue(std::string triggerName, float value)
{
	auto it = floatTriggers.find(triggerName);
	ASSERT(it != floatTriggers.end(), "Error: trigger name could not be found");
	it->second.trigger = value;
}

void AnimationController::CreateState(std::string stateName, AnimationClip* animationClip)
{
	AnimationState* newState = new AnimationState();
	newState->name = stateName;
	uint32_t index = static_cast<uint32_t>(animationClips.size());
	newState->ClipIndex = index;
	states.push_back(newState);
	animationClips.try_emplace(index, animationClip);
}

void AnimationController::SetState(std::string stateName, AnimationClip* animationClip)
{
	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (states[i]->name == stateName)
		{
			auto it = animationClips.find(states[i]->ClipIndex);
			if (it == animationClips.end())
			{
				animationClips.try_emplace(states[i]->ClipIndex, animationClip);
				break;
			}
			it->second = animationClip;
			break;
		}
	}
}

AnimationClip* AnimationController::GetCurrentAnimation()
{
	/*if (mCurrentState->BlendClip != nullptr)
	{
		return mCurrentState->BlendClip;
	}*/
	auto it = animationClips.find(mCurrentState->ClipIndex);
	if (it != animationClips.end())
	{
		return it->second;
	}
	return nullptr;
	
}

void AnimationController::SetCurrentState(std::string stateName)
{
	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (states[i]->name == stateName)
		{
			mCurrentState = states[i];
			break;
		}
	}
}

void AnimationController::CreateTransition(std::string fromState, std::string toState, 
											std::string triggerKey, bool triggerValue)
{
	ASSERT(fromState != toState, "Error: From state and To state should be different");
	Transition<bool> newTransition;
	newTransition.triggerName = triggerKey;
	newTransition.valueToTrigger = triggerValue;

	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (fromState == states[i]->name)
		{
			newTransition.from = states[i];
			states[i]->transitionBoolIndices.push_back(static_cast<uint32_t>(transitionsBool.size()));
			break;
		}
		newTransition.from = nullptr;
	}
	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (toState == states[i]->name)
		{
			newTransition.to = states[i];
			break;
		}
		newTransition.to = nullptr;
	}

	if (newTransition.from != nullptr && newTransition.to != nullptr)
	{
		transitionsBool.push_back(newTransition);
	}

}


void AnimationController::CreateTransition(std::string fromState, std::string toState, 
											std::string triggerKey, int triggerValue)
{
	ASSERT(fromState != toState, "Error: From state and To state should be different");
	Transition<int> newTransition;
	newTransition.triggerName = triggerKey;
	newTransition.valueToTrigger = triggerValue;

	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (fromState == states[i]->name)
		{
			newTransition.from = states[i];
			states[i]->transitionIntIndices.push_back(static_cast<uint32_t>(transitionsInt.size()));
			break;
		}
		newTransition.from = nullptr;
	}
	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (toState == states[i]->name)
		{
			newTransition.to = states[i];
			break;
		}
		newTransition.to = nullptr;
	}

	if (newTransition.from != nullptr && newTransition.to != nullptr)
	{
		transitionsInt.push_back(newTransition);
	}

}

void AnimationController::CreateTransition(std::string fromState, std::string toState,
	std::string triggerKey, float triggerValue)
{
	ASSERT(fromState != toState, "Error: From state and To state should be different");
	Transition<float> newTransition;
	newTransition.triggerName = triggerKey;
	newTransition.valueToTrigger = triggerValue;

	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (fromState == states[i]->name)
		{
			newTransition.from = states[i];
			states[i]->transitionFloatIndices.push_back(static_cast<uint32_t>(transitionsFloat.size()));
			break;
		}
		newTransition.from = nullptr;
	}
	for (uint32_t i = 0; i < states.size(); ++i)
	{
		if (toState == states[i]->name)
		{
			newTransition.to = states[i];
			break;
		}
		newTransition.to = nullptr;
	}

	if (newTransition.from != nullptr && newTransition.to != nullptr)
	{
		transitionsFloat.push_back(newTransition);
	}

}

void AnimationController::AnimationControllerUpdate()
{
	if (!mCurrentState->HasTransition())
	{
		return;
	}

	for (uint32_t i = 0; i < mCurrentState->transitionBoolIndices.size(); ++i)
	{
		auto it = boolTriggers.find(transitionsBool[mCurrentState->transitionBoolIndices[i]].triggerName);
		if (transitionsBool[mCurrentState->transitionBoolIndices[i]].valueToTrigger == it->second.trigger)
		{
			/*auto it = animationClips.find(mCurrentState->ClipIndex);*/
			/*AnimationClip* from = it->second;*/
			mCurrentState = transitionsBool[mCurrentState->transitionBoolIndices[i]].to;
			/*auto it = animationClips.find(mCurrentState->ClipIndex);*/
			/*AnimationClip* to = it->second;*/
			/*mCurrentState->BlendClip = CreateBlendClip(from, to);*/
			
			return;
		}
	}

	for (uint32_t i = 0; i < mCurrentState->transitionIntIndices.size(); ++i)
	{
		auto it = intTriggers.find(transitionsInt[mCurrentState->transitionIntIndices[i]].triggerName);
		int valueToTrigger = transitionsInt[mCurrentState->transitionIntIndices[i]].valueToTrigger;
		int conditionVariable = it->second.trigger;
		switch (it->second.conditionalEnum)
		{
		case TriggerConditional::EQUALS:
			if (valueToTrigger == conditionVariable)
			{
				mCurrentState = transitionsInt[mCurrentState->transitionIntIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::GREATER_THAN:
			if (valueToTrigger > conditionVariable)
			{
				mCurrentState = transitionsInt[mCurrentState->transitionIntIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::GREATER_THAN_OR_EQUAL:
			if (valueToTrigger >= conditionVariable)
			{
				mCurrentState = transitionsInt[mCurrentState->transitionIntIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::LESS_THAN:
			if (valueToTrigger < conditionVariable)
			{
				mCurrentState = transitionsInt[mCurrentState->transitionIntIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::LESS_THAN_OR_EQUAL:
			if (valueToTrigger <= conditionVariable)
			{
				mCurrentState = transitionsInt[mCurrentState->transitionIntIndices[i]].to;
				return;
			}
			break;
		}
	}


	for (uint32_t i = 0; i < mCurrentState->transitionFloatIndices.size(); ++i)
	{
		auto it = floatTriggers.find(transitionsFloat[mCurrentState->transitionFloatIndices[i]].triggerName);
		float valueToTrigger = transitionsFloat[mCurrentState->transitionFloatIndices[i]].valueToTrigger;
		float conditionVariable = it->second.trigger;
		switch (it->second.conditionalEnum)
		{
		case TriggerConditional::EQUALS:
			if (valueToTrigger == conditionVariable)
			{
				mCurrentState = transitionsFloat[mCurrentState->transitionFloatIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::GREATER_THAN:
			if (valueToTrigger > conditionVariable)
			{
				mCurrentState = transitionsFloat[mCurrentState->transitionFloatIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::GREATER_THAN_OR_EQUAL:
			if (valueToTrigger >= conditionVariable)
			{
				mCurrentState = transitionsFloat[mCurrentState->transitionFloatIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::LESS_THAN:
			if (valueToTrigger < conditionVariable)
			{
				mCurrentState = transitionsFloat[mCurrentState->transitionFloatIndices[i]].to;
				return;
			}
			break;
		case TriggerConditional::LESS_THAN_OR_EQUAL:
			if (valueToTrigger <= conditionVariable)
			{
				mCurrentState = transitionsFloat[mCurrentState->transitionFloatIndices[i]].to;
				return;
			}
			break;
		}
	}
}