#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"
#include <Core/Inc/MetaClass.h>
#include "World.h"

using namespace ZERO;
using namespace ZERO::Engine;


GameObject::GameObject()
{}

GameObject::~GameObject()
{
	Terminate();
}


void GameObject::Initialize()
{
	for (auto& component : mComponents)
	{
		component->Initialize();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	for (auto& component : mComponents)
	{
		component->Render();
	}
}

void GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		component->Terminate();
	}
	mComponents.clear();
}

Component* GameObject::GetComponentAt(size_t index)
{
	return mComponents[index].get();
}

Component* GameObject::GetComponentByMetaClass(const ZERO::Core::Meta::MetaClass* metaclass)
{
	Component* comp = nullptr;
	for (size_t i = 0; i < mComponents.size(); ++i)
	{
		if (mComponents[i].get()->GetMetaClass() == metaclass)
		{
			comp = mComponents[i].get();
			break;
		}
	}

	return comp;
}

//void GameObject::LoadGameObject(const char* filePathXML, std::string name)
//{
//	mName = name;
//	tinyxml2::XMLDocument doc;
//	XMLError er = doc.LoadFile(filePathXML);
//
//	XMLNode* pRoot = doc.FirstChild();
//	ASSERT(pRoot, "[XMLError] Could not read xml file.");
//	if (pRoot)
//	{
//
//		XMLElement* pComponent = pRoot->FirstChildElement("Components");
//		if (pComponent != nullptr)
//		{
//			//Transform
//			XMLElement* pTransform = pComponent->FirstChildElement("TransformComponent");
//			if (pTransform)
//			{
//				//Add Transform Component
//				TransformComponent* transform = AddComponent<TransformComponent>();
//				XMLElement* pVector = pTransform->FirstChildElement("Vector3");
//				if (pVector)
//				{
//					XMLElement* pFloat = pVector->FirstChildElement("Float");
//					int index = 0;
//					float xyz[3];
//					while (pFloat)
//					{
//						XMLNode* pFloatNode = pFloat->FirstChild();
//						xyz[index] = static_cast<float>(std::atof(pFloatNode->Value()));
//						pFloat = pFloat->NextSiblingElement();
//						index++;
//					}
//					Math::Vector3 pos = { xyz[0], xyz[1], xyz[2] };
//					GetComponent<TransformComponent>()->SetPosition(pos);
//				}
//			}
//			//Collider
//			XMLElement* pColliderComponent = pComponent->FirstChildElement("ColliderComponent");
//			std::vector<float> colliderValues;
//			if (pColliderComponent)
//			{
//				//Add Collider Component
//				ColliderComponent* collider = AddComponent<ColliderComponent>();
//				/*collider->Initialize();*/
//				XMLElement* pVector = pColliderComponent->FirstChildElement("Vector3");
//				while (pVector)
//				{
//					XMLElement* pFloat = pVector->FirstChildElement("Float");
//					while (pFloat)
//					{
//						XMLNode* pFloatNode = pFloat->FirstChild();
//						colliderValues.push_back(static_cast<float>(std::atof(pFloatNode->Value())));
//						pFloat = pFloat->NextSiblingElement();
//					}
//					pVector = pVector->NextSiblingElement();
//				}
//
//				collider->SetCenter(Math::Vector3(colliderValues[0], colliderValues[1], colliderValues[2]));
//				collider->SetExtent(Math::Vector3(colliderValues[3], colliderValues[4], colliderValues[5]));
//				collider->SetColor (Math::Vector4(colliderValues[6], colliderValues[7], colliderValues[8], colliderValues[9]));
//			}
//
//		}
//	}
//}

Component* GameObject::AddComponent(const ZERO::Core::Meta::MetaClass* metaClass)
{
	mComponents.emplace_back(static_cast<Component*>(metaClass->Create()));
	auto& newComponent = mComponents.back();
	newComponent->mGameObject = this;
	return newComponent.get();
	
}