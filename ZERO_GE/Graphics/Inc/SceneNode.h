#ifndef INCLUDED_GRAPHICS_SCENENODE_H
#define INCLUDED_GRAPHICS_SCENENODE_H

namespace ZERO
{
namespace Graphics
{
class SceneNode
{
public:
	SceneNode();
	virtual ~SceneNode();

	bool AddChild(SceneNode* child);
	bool RemoveChild(const char* name);
	bool RemoveChild(uint32_t id);

	void Update(float deltaTime);
	void Render();

	void SetName(const char* name) { mName = name; }
	void SetId(uint32_t id) { mId = id; }

	void SetEnable(bool enabled) { mEnabled = enabled; }

	const char* GetName() const { return mName.c_str(); }
	uint32_t GetId() const { return mId; }

protected:
	typedef std::vector<SceneNode*> SceneNodeList;

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnPreRender() {}
	virtual void OnRender() {}
	virtual void OnPostRender() {}

	SceneNode* mpParent;
	SceneNodeList mChildren;

	std::string mName;
	uint32_t mId;

	bool mEnabled;
};

}// !namespace Graphics
}// !namespace ZERO



#endif //!INCLUDED_GRAPHICS_SCENENODE_H