#pragma once

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <Engine/Inc/Engine.h>


using namespace ZERO;
using namespace ZERO::Core;
using namespace ZERO::Engine;

class FrontEnd : public State
{
public:
	FrontEnd();
	void Load() override;
	std::string Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void ImGuiFrontEnd();
private:
	GameObject* blueBox;
	GameObject* redBox;
	GameObject* greenBox;
	GameObjectFactory mGameObjectFactory;
	GameObjectAllocator mGameObjectAllocator;
};
