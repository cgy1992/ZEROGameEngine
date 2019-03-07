
//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "SceneNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
using namespace ZERO;
using namespace ZERO::SCENE;

SceneNode::SceneNode()
	: mpParent(nullptr)
	, mName("Unknown")
	, mId(-1)
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
	const uint32_t numChildren = mChildren.size();
	for (uint32_t i = 0; i < numChildren; ++i)
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
	const uint32_t numChildren = mChildren.size();
	for (uint32_t i = 0; i < numChildren; ++i)
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
	OnUpdate(deltaTime);

	for (SceneNode* child : mChildren)
	{
		child->Update(deltaTime);
	}
}

//----------------------------------------------------------------------------------------------------

void SceneNode::Render()
{
	OnPreRender();
	OnRender();
	
	for (SceneNode* child : mChildren)
	{
		child->Render();
	}

	OnPostRender();
}