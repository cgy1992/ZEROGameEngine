#ifndef INCLUDED_ENGINE_GAMEOBJECTFACTORY_H
#define INCLUDED_ENGINE_GAMEOBJECTFACTORY_H

#include "GameObject.h"

namespace ZERO
{
namespace Engine
{
class GameObjectFactory
{
using GameObjectAllocator = Core::TypedAllocator<GameObject>;
public:
	GameObjectFactory(GameObjectAllocator& allocator);

	GameObject* Create(const char* templateFileName);
	void Destroy(GameObject* gameObject);

private:
	GameObjectAllocator& mGameObjectAllocattor;
};

}//!namespace Engine
}//!namespace ZERO



#endif

