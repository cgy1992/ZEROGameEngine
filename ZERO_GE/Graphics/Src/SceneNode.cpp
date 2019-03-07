
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "SceneNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::Graphics;

SceneNode::SceneNode()
	: mpParent(nullptr)
	, mName("Unknown")
	, mId(-1)
	, mEnabled(true)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SceneNode::~SceneNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

bool SceneNode::AddChild(SceneNode* child)
{
	// Add child to list and set self to be parent
	mChildren.push_back(child);
	child->mpParent = this;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool SceneNode::RemoveChild(const char* name)
{
	const size_t numChildren = mChildren.size();
	for (size_t i = 0; i < numChildren; ++i)
	{
		if (mChildren[i]->mName == name)
		{
			mChildren[i] = mChildren[numChildren - 1];
			mChildren.pop_back();
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

bool SceneNode::RemoveChild(uint32_t id)
{
	const size_t numChildren = mChildren.size();
	for (size_t i = 0; i < numChildren; ++i)
	{
		if (mChildren[i]->mId == id)
		{
			mChildren[i] = mChildren[numChildren - 1];
			mChildren.pop_back();
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

void SceneNode::Update(float deltaTime)
{
	if (true == mEnabled)
	{
		OnUpdate(deltaTime);

		for (SceneNode* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}
}

//----------------------------------------------------------------------------------------------------

void SceneNode::Render()
{
	if (true == mEnabled)
	{
		OnPreRender();
		OnRender();

		for (SceneNode* child : mChildren)
		{
			child->Render();
		}

		OnPostRender();
	}
	
}