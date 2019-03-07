#ifndef INCLUDED_ENGINE_GAMEAPP_H
#define INCLUDED_ENGINE_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <External/ImGui/Inc/imgui.h>
#include "World.h"


namespace ZERO
{
namespace Engine
{
class GameApp : public Core::Application
{
public:
	GameApp();
	~GameApp() override;

	template<class T>
	void AddState() { mStateMachine.AddState<T>(); }
	/*Graphics::Camera MainCamera() const { return mCamera; }*/
	
private:
	void OnInitialize() override;
	void OnTerminate() override;
	void OnUpdate() override;

	
	void ControlCamera(float dt, Input::InputSystem* is);

	Core::Window mWindow;
	Core::Timer mTimer;
	/*Graphics::Camera mCamera;*/
	ZERO::Engine::World myWorld;
	Core::StateMachine mStateMachine;
};

}
}

#endif