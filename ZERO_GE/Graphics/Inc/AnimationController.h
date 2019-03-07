#ifndef INCLUDED_GRAPHICS_ANIMATIONCONTROLLER
#define INCLUDED_GRAPHICS_ANIMATIONCONTROLLER

#include "AnimationClip.h"

namespace ZERO
{
namespace Graphics
{

enum class TriggerConditional
{
	EQUALS,
	GREATER_THAN,
	LESS_THAN,
	GREATER_THAN_OR_EQUAL,
	LESS_THAN_OR_EQUAL
};

struct AnimationState
{
	std::string name;
	uint32_t ClipIndex;
	std::vector<uint32_t> transitionBoolIndices;
	std::vector<uint32_t> transitionIntIndices;
	std::vector<uint32_t> transitionFloatIndices;

	bool HasTransition() const
	{
		if (transitionBoolIndices.size() == 0 && transitionFloatIndices.size() == 0 && transitionIntIndices.size() == 0)
		{
			return false;
		}
		return true;
	}

};

template<typename T>
struct Transition
{
	AnimationState* from;
	AnimationState* to;
	std::string triggerName;
	T valueToTrigger;
};

struct BoolTrigger
{
	bool trigger;
};

struct IntTrigger
{
	int trigger;
	TriggerConditional conditionalEnum;
};

struct FloatTrigger
{
	float trigger;
	TriggerConditional conditionalEnum;
};

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	AnimationController(const AnimationController& other) = delete;
	AnimationController& operator=(const AnimationController& other) = delete;


	void AddTrigger(std::string name, bool currentValue);
	void AddTrigger(std::string name, int currentValue, TriggerConditional currentConditionalEnum);
	void AddTrigger(std::string name, float currentValue, TriggerConditional currentConditionalEnum);

	void SetTrigger(std::string triggerName);
	void SetTriggerValue(std::string triggerName, int value);
	void SetTriggerValue(std::string triggerName, float value);


	void CreateState(std::string stateName, AnimationClip* animationClip);
	void SetState(std::string stateName, AnimationClip* animationClip);
	AnimationState* GetCurrentState() const { return mCurrentState; }
	AnimationClip* GetCurrentAnimation();
	void SetCurrentState(std::string stateName);

	void CreateTransition(std::string fromState, std::string toState, std::string triggerKey, bool  triggerValue);
	void CreateTransition(std::string fromState, std::string toState, std::string triggerKey, int   triggerValue);
	void CreateTransition(std::string fromState, std::string toState, std::string triggerKey, float triggerValue);

	void AnimationControllerUpdate();
private:
	AnimationClip* CreateBlendClip(AnimationClip* from, AnimationClip* to);

	//Triggers to change state
	std::map<std::string, BoolTrigger> boolTriggers;
	std::map<std::string, FloatTrigger> floatTriggers;
	std::map<std::string, IntTrigger> intTriggers;

	//Animation clips and index
	std::map<uint32_t, AnimationClip*> animationClips;
	std::vector<AnimationState*> states;
	std::vector<Transition<bool>> transitionsBool;
	std::vector<Transition<int>> transitionsInt;
	std::vector<Transition<float>> transitionsFloat;
	AnimationState* mCurrentState;
	float mBlendTime{ 0.7f };
};
}
}

#endif // !INCLUDED_GRAPHICS_ANIMATIONCONTROLLER
