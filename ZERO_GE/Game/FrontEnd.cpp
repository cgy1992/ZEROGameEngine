#include "FrontEnd.h"

namespace
{
	int currItem{ 1 };
	bool menu1, menu2, menu3 = false;
}

FrontEnd::FrontEnd()
	: mGameObjectAllocator(100)
	, mGameObjectFactory(mGameObjectAllocator)
	, blueBox(nullptr)
	, redBox(nullptr)
	, greenBox(nullptr)
{
	SetName("FrontEnd");
}

void FrontEnd::Load()
{
	
	/*blueBox = mGameObjectFactory.Create("../Assets/Data/blue_box.xml");
	blueBox->SetName("BlueBox");

	redBox = mGameObjectFactory.Create("../Assets/Data/red_box.xml");
	redBox->SetName("RedBox");

	greenBox = mGameObjectFactory.Create("../Assets/Data/green_box.xml");
	greenBox->SetName("GreenBox");

	blueBox->Initialize();
	redBox->Initialize();
	greenBox->Initialize();*/
}

std::string FrontEnd::Update(float deltaTime)
{
	std::string sceneName = GetName();
	Input::InputSystem* is = Input::InputSystem::Get();
	
	/*blueBox->Update(deltaTime);
	redBox->Update(deltaTime);
	greenBox->Update(deltaTime);*/
	
	Gui::BeginRender(deltaTime);

	if (is->IsKeyPressed(Input::KeyCode::F2))
	{
		sceneName = "Scene_1";
	}

	return sceneName;
}

void FrontEnd::Render()
{
	/*blueBox->Render();
	redBox->Render();
	greenBox->Render();*/
	
	ImGuiFrontEnd();
	Gui::EndRender();
}

void FrontEnd::Unload()
{
	/*blueBox->Terminate();
	redBox->Terminate();
	greenBox->Terminate();*/
}

void FrontEnd::ImGuiFrontEnd()
{
	//ImGui::SetNextWindowSize(ImVec2(320, 500), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowPos(ImVec2(50, 50));
	//ImGui::Begin("Hierarchy");
	//const char* items[] = { blueBox->GetName().c_str(), redBox->GetName().c_str(), greenBox->GetName().c_str() };
	//ImGui::ListBox("Objects", &currItem, items, 3, IM_ARRAYSIZE(items));
	//ImGui::End();

	//ImGui::SetNextWindowSize(ImVec2(320, 500), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowPos(ImVec2(900, 50));
	//ImGui::Begin("Inspector");
	//switch (currItem)
	//{
	//case 0:
	//	if (ImGui::CollapsingHeader("Components"))
	//	{
	//		TransformComponent* transform = (TransformComponent*)blueBox->GetComponentAt(0);
	//		ColliderComponent* collider = (ColliderComponent*)blueBox->GetComponentAt(1);
	//		float transformFloat[3];
	//		transformFloat[0] = transform->GetPosition().x;
	//		transformFloat[1] = transform->GetPosition().y;
	//		transformFloat[2] = transform->GetPosition().z;

	//		float colliderExtFloat[3];
	//		colliderExtFloat[0] = collider->GetExtent().x;
	//		colliderExtFloat[1] = collider->GetExtent().y;
	//		colliderExtFloat[2] = collider->GetExtent().z;


	//		ImGui::DragFloat3("Transform", transformFloat,0.1f, -100.0f, 100.0f);
	//		ImGui::DragFloat3("Extent", colliderExtFloat, 0.1f, -100.0f, 100.0f);
	//		
	//		transform->SetPosition(Math::Vector3(transformFloat[0], transformFloat[1], transformFloat[2]));
	//		collider->SetExtent(Math::Vector3(colliderExtFloat[0], colliderExtFloat[1], colliderExtFloat[2]));
	//	
	//	}
	//	break;
	//case 1:
	//	if (ImGui::CollapsingHeader("Components"))
	//	{

	//		TransformComponent* transform = (TransformComponent*)redBox->GetComponentAt(0);
	//		ColliderComponent* collider = (ColliderComponent*)redBox->GetComponentAt(1);
	//		float transformFloat[3];
	//		transformFloat[0] = transform->GetPosition().x;
	//		transformFloat[1] = transform->GetPosition().y;
	//		transformFloat[2] = transform->GetPosition().z;

	//		float colliderExtFloat[3];
	//		colliderExtFloat[0] = collider->GetExtent().x;
	//		colliderExtFloat[1] = collider->GetExtent().y;
	//		colliderExtFloat[2] = collider->GetExtent().z;


	//		ImGui::DragFloat3("Transform", transformFloat, 0.1f, -100.0f, 100.0f);
	//		ImGui::DragFloat3("Extent", colliderExtFloat, 0.1f, -100.0f, 100.0f);

	//		transform->SetPosition(Math::Vector3(transformFloat[0], transformFloat[1], transformFloat[2]));
	//		collider->SetExtent(Math::Vector3(colliderExtFloat[0], colliderExtFloat[1], colliderExtFloat[2]));
	//	}
	//	break;
	//case 2:
	//	if (ImGui::CollapsingHeader("Components"))
	//	{

	//		TransformComponent* transform = (TransformComponent*)greenBox->GetComponentAt(0);
	//		ColliderComponent* collider = (ColliderComponent*)greenBox->GetComponentAt(1);
	//		float transformFloat[3];
	//		transformFloat[0] = transform->GetPosition().x;
	//		transformFloat[1] = transform->GetPosition().y;
	//		transformFloat[2] = transform->GetPosition().z;

	//		float colliderExtFloat[3];
	//		colliderExtFloat[0] = collider->GetExtent().x;
	//		colliderExtFloat[1] = collider->GetExtent().y;
	//		colliderExtFloat[2] = collider->GetExtent().z;


	//		ImGui::DragFloat3("Transform", transformFloat, 0.1f, -100.0f, 100.0f);
	//		ImGui::DragFloat3("Extent", colliderExtFloat, 0.1f, -100.0f, 100.0f);

	//		transform->SetPosition(Math::Vector3(transformFloat[0], transformFloat[1], transformFloat[2]));
	//		collider->SetExtent(Math::Vector3(colliderExtFloat[0], colliderExtFloat[1], colliderExtFloat[2]));
	//	}
	//default:
	//	break;
	//}
	//ImGui::End();
}
