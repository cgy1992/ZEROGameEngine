#include "Precompiled.h"
#include "StateMachine.h"

#include "Debug.h"
#include "State.h"

using namespace ZERO;
using namespace Core;

StateMachine::StateMachine()
	: mCurrentState(nullptr)
{}

StateMachine::~StateMachine()
{}

//void StateMachine::AddState(State* state)
//{
//	
//}

void StateMachine::ChangeState(uint32_t index)
{
	ASSERT(index > mStates.size(), "[StateMachine] Index is out of range.");
	mCurrentState = mStates[index].get();
}

void StateMachine::ChangeState(std::string name)
{
	bool find = false;
	uint32_t index = 0;
	for (uint32_t i=0; i < mStates.size(); ++i)
	{
		if (mStates[i]->GetName() == name)
		{
			find = true;
			break;
		}
		index++;
	}

	ASSERT(find, "[StateMachine] State Name is does not exist");
	mCurrentState = mStates[index].get();
}


void StateMachine::Purge()
{
	mStates.clear();
	mCurrentState = nullptr;
}

void StateMachine::InitializeStates()
{
	for (uint32_t i = 0; i < mStates.size(); ++i)
	{
		mStates[i]->Load();
	}
}

void StateMachine::UpdateState(float deltaTime)
{
	ASSERT(mCurrentState != nullptr, "[StateMachine] Current State is null.");
	std::string name = mCurrentState->Update(deltaTime);
	
	if (name != mCurrentStateName)
	{
		ChangeState(name);
		mCurrentStateName = name;
	}
}

void StateMachine::RenderState()
{
	ASSERT(mCurrentState != nullptr, "[StateMachine] Current State is null.");
	mCurrentState->Render();
}

void StateMachine::TerminateStates()
{
	for (uint32_t i = 0; i < mStates.size(); ++i)
	{
		mStates[i]->Unload();
	}
}