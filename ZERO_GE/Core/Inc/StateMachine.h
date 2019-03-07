#ifndef INCLUDED_CORE_STATEMACHINE_H
#define INCLUDED_CORE_STATEMACHINE_H

#include "Debug.h"

namespace ZERO
{
namespace Core
{
class State;


class StateMachine
{
public:
	using States = std::vector<std::unique_ptr<State>>;

	StateMachine();
	~StateMachine();

	void InitializeStates();
	void UpdateState(float deltaTime);
	void RenderState();
	void TerminateStates();

	template<class T>
	void AddState()
	{
		//ASSERT(std::is_base_of_v<T, State>, "[StateMachine] Can only add state from State type.");
		static_assert(std::is_base_of<State, T>::value,
			"[StateMachine] Can only add state for State");
		mStates.emplace_back(std::make_unique<T>());

		if (mStates.size() == 1)
		{
			//If the size is equals 1, point mcurrentState 
			//to the first element of the array
			mCurrentState = mStates[0].get();
			mCurrentStateName = mCurrentState->GetName();
		}
	}

	void Purge();

	void ChangeState(uint32_t index);
	void ChangeState(std::string name);

private:
	State* mCurrentState;
	std::string mCurrentStateName;
	States mStates;
};



}//!namespace core
}//!namespace ZERO



#endif // !INCLUDED_CORE_STATEMACHINE_H
