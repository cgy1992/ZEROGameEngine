#ifndef INCLUDED_ENGINE_COMPONENT_H
#define INCLUDED_ENGINE_COMPONENT_H

namespace ZERO
{
namespace Engine
{

class GameObject;

class Component
{
public:
	META_CLASS_DECLARE
	Component();
	virtual ~Component();

	virtual void Initialize() {}
	virtual void Terminate() {}

	virtual void Update(float deltatime) {}
	virtual void Render() {}

	GameObject& GetOwner() { return *mGameObject; }
	const GameObject& GetOwner() const { return *mGameObject; }

private:
	friend class GameObject;
	GameObject* mGameObject;
	std::string mName;

};
}
}



#endif // !INCLUDED_ENGINE_COMPONENT_H

