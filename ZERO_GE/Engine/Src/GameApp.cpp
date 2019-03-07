#include "Precompiled.h"
#include "GameApp.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "MetaRegistration.h"
#include "CameraComponent.h"

using namespace ZERO;
using namespace ZERO::Engine;

namespace
{
	uint32_t width = 1600;
	uint32_t height = 900;
}

GameApp::GameApp()
{
	
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize()
{
	Meta::MetaRegister();


	//System Initialization
	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 768);
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Gui::Initialize(mWindow.GetWindowHandle());
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	Graphics::SimpleDraw::Initialize(99999);
	/*mCamera.SetLens(0.25f * Math::kPi, (float)width, (float)height, 0.5f, 1000.0f);
	mCamera.SetPosition({ 0.0f, 60.0f, -100.0f });
	mCamera.CreatePerspectiveMatrix();*/
	

	mTimer.Initialize();

	myWorld.Initialize(1000);
	myWorld.LoadLevel("../Assets/Data/level.xml");

	//States Initialization
	mStateMachine.InitializeStates();
}

void GameApp::OnTerminate()
{
	//Terminating systems
	myWorld.Terminate();
	Graphics::SimpleDraw::Terminate();
	Gui::Terminate();
	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();
	mWindow.Terminate();

	//Terminate States
	mStateMachine.TerminateStates();
}


void GameApp::OnUpdate()
{
	mTimer.Update();
	float deltaTime = mTimer.GetElapsedTime();

	Input::InputSystem* is = Input::InputSystem::Get();

	is->Update();

	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

	if (is->IsKeyPressed(Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}
	
	//Update Current State
	mStateMachine.UpdateState(deltaTime);

	myWorld.Update(deltaTime);
	

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	//Render State
	mStateMachine.RenderState();

	Graphics::SimpleDraw::Render(*myWorld.Find("MainCamera")->GetComponent<CameraComponent>()->GetCamera());

	myWorld.Render();

	graphicsSystem->EndRender();
	//Check to exit

}
