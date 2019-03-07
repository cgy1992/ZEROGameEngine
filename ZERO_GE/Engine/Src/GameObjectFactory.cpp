#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "Component.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "XMLReader.h"



using namespace ZERO;
using namespace ZERO::Engine;
using namespace tinyxml2;

GameObjectFactory::GameObjectFactory(GameObjectAllocator& allocator)
	:mGameObjectAllocattor(allocator)
{}


GameObject* GameObjectFactory::Create(const char* templateFileName)
{
	GameObject* gameObject = mGameObjectAllocattor.New();

	tinyxml2::XMLDocument doc;
	XMLError er = doc.LoadFile(templateFileName);

	XMLNode* pRoot = doc.FirstChild();
	ASSERT(pRoot, "[XMLError] Could not read xml file.");
	if (strcmp(pRoot->Value(), "GameObject") == 0) 
	{
		const XMLElement* pComponent = pRoot->FirstChildElement("Components");
		if (pComponent != nullptr)
		{
			const XMLNode* nextCompNode = pComponent->FirstChild();
			while (nextCompNode != nullptr)
			{
				const char* componentName = nextCompNode->Value();

				const ZERO::Core::Meta::MetaClass* metaClass = ZERO::Core::Meta::MetaRegistry::FindMetaClass(componentName);
				if (metaClass == nullptr)
				{
					LOG("Class [%s] not registered with the meta system", componentName)
				}
				else
				{
					const auto newComponent = gameObject->AddComponent(metaClass);
					const XMLNode* data = nextCompNode->FirstChild();
					VERIFY(XMLReader::Read(newComponent, metaClass, data), "Failed to read %s", componentName);
				}

				nextCompNode = nextCompNode->NextSibling();
			}
		}
	}
	
	return gameObject;
}

void GameObjectFactory::Destroy(GameObject* gameObject)
{
	mGameObjectAllocattor.Delete(gameObject);
}

//Transform
//XMLElement* pTransform = pComponent->FirstChildElement("TransformComponent");
//if (pTransform)
//{
//	//Add Transform Component
//	TransformComponent* transform = gameObject->AddComponent<TransformComponent>();
//	XMLElement* pVector = pTransform->FirstChildElement("Vector3");
//	if (pVector)
//	{
//		XMLElement* pFloat = pVector->FirstChildElement("Float");
//		int index = 0;
//		float xyz[3];
//		while (pFloat)
//		{
//			XMLNode* pFloatNode = pFloat->FirstChild();
//			xyz[index] = static_cast<float>(std::atof(pFloatNode->Value()));
//			pFloat = pFloat->NextSiblingElement();
//			index++;
//		}
//		Math::Vector3 pos = { xyz[0], xyz[1], xyz[2] };
//		transform->SetPosition(pos);
//	}
//}
////Collider
//XMLElement* pColliderComponent = pComponent->FirstChildElement("ColliderComponent");
//std::vector<float> colliderValues;
//if (pColliderComponent)
//{
//	//Add Collider Component
//	ColliderComponent* collider = gameObject->AddComponent<ColliderComponent>();
//	/*collider->Initialize();*/
//	XMLElement* pVector = pColliderComponent->FirstChildElement("Vector3");
//	while (pVector)
//	{
//		XMLElement* pFloat = pVector->FirstChildElement("Float");
//		while (pFloat)
//		{
//			XMLNode* pFloatNode = pFloat->FirstChild();
//			colliderValues.push_back(static_cast<float>(std::atof(pFloatNode->Value())));
//			pFloat = pFloat->NextSiblingElement();
//		}
//		pVector = pVector->NextSiblingElement();
//	}

//	collider->SetCenter(Math::Vector3(colliderValues[0], colliderValues[1], colliderValues[2]));
//	collider->SetExtent(Math::Vector3(colliderValues[3], colliderValues[4], colliderValues[5]));
//	collider->SetColor(Math::Vector4(colliderValues[6], colliderValues[7], colliderValues[8], colliderValues[9]));
//}