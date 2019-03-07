#include "Scene_1.h"

Scene1::Scene1()
{
	SetName("Scene_1");
}

void Scene1::Load()
{
	SetName("Scene_1");
}

std::string Scene1::Update(float deltaTime)
{
	std::string sceneName = GetName();
	Input::InputSystem* is = Input::InputSystem::Get();
	ZERO::Graphics::SimpleDraw::AddCube(10.0f, ZERO::Math::Vector3::Zero(), ZERO::Math::Vector4::Red());

	if (is->IsKeyPressed(Input::KeyCode::F1))
	{
		sceneName = "FrontEnd";
	}

	return sceneName;
}

void Scene1::Render()
{
	
}

void Scene1::Unload()
{

}
