#ifndef INCLUDED_ENGINE_GAMEOBJECT_H
#define INCLUDED_ENGINE_GAMEOBJECT_H

#include <Core/Inc/TypedAllocator.h>
#include <Core/Inc/HandlePool.h>
#include "Component.h"


namespace ZERO
{
namespace Engine
{

class Component;
class GameObject;
class MetaClass;
class World;


using GameObjectHandle = Core::Handle<GameObject>;
using GameObjectAllocator = Core::TypedAllocator<GameObject>;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Initialize();
	void Terminate();

	void Update(float deltaTime);
	void Render();

	//void LoadGameObject(const char* filePathXML, std::string name);
	
	template<class T>
	typename std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent();

	template<class T>
	T* GetComponent();


	/*Component* GetComponentByName(const char* name);*/

	Component* GetComponentByMetaClass(const ZERO::Core::Meta::MetaClass* metaclass);

	Component* AddComponent(const ZERO::Core::Meta::MetaClass* metaClass);
	
	Component* GetComponentAt(size_t index);

	size_t GetComponentCount() const		{ return mComponents.size();	}
	GameObjectHandle GetHandle()			{ return mHandle;				}
	const std::string& GetName() const		{ return mName;					}
	void SetName(std::string name)			{ mName = name;					}
	World& GetWorld()						{ return *mWorld; }

private:
	friend class World;
	using Components = std::vector<std::unique_ptr<Component>>;

	World* mWorld{ nullptr };
	std::string mName;
	GameObjectHandle mHandle;
	std::vector<GameObject> mChildren;

	Components mComponents;

};

template<class T>
typename std::enable_if_t<std::is_base_of_v<Component, T>, T*>
GameObject::AddComponent()
{
	mComponents.push_back(std::make_unique<T>());
	auto& newComponent = mComponents[mComponents.size() - 1];
	newComponent->mGameObject = this;
	return static_cast<T*>(newComponent.get());
}

template<class T>
T* GameObject::GetComponent()
{
	T* result = nullptr;
	for (auto& component : mComponents)
	{
		//if this is the right component
		if (component->GetMetaClass() == T::StaticGetMetaClass())
		{
			result = static_cast<T*>(component.get());
			break;
		}
	}

	return result;
}


//Component* GameObject::GetComponentByName(const char* name)
//{
//	Component* comp = nullptr;
//	for (uint32_t i = 0; i<mComponents.size(); ++i)
//	{
//		if (strcmp(mComponents[i]->GetName().c_str(), name) == 0)
//		{
//			comp = mComponents[i].get();
//			break;
//		}
//	}
//
//	return comp;
//}

}//!namespace 
}
#endif // !INCLUDED_ENGINE_GAMEOBJECT_H

