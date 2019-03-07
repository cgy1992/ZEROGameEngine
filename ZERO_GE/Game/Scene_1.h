#pragma once

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>

using namespace ZERO;
using namespace ZERO::Core;

class Scene1 : public State
{
public:
	Scene1();
	void Load() override;
	std::string Update(float deltaTime) override;
	void Render() override;
	void Unload() override;
};
