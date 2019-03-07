#ifndef INCLUDED_ENGINE_WORLD_H
#define INCLUDED_ENGINE_WORLD_H

#include "GameObjectFactory.h"
#include "VertexShaderResourceManager.h"
#include "PixelShaderResourceManager.h"
#include "TextureResourceManager.h"
#include "PrimitiveMeshResourceManager.h"


namespace tinyxml2
{
	class XMLNode;
}
namespace ZERO
{
namespace Engine
{

class World
{
using GameObjectHandlePool = Core::HandlePool<GameObject>;
public:
	void Initialize(uint32_t capacity);
	void Terminate();

	void LoadLevel(const char* levelFileName);

	GameObjectHandle Create(const char* templateFileName, const char* name);
	GameObjectHandle Find(const char* name);
	void Destroy(GameObjectHandle handle);

	void Update(float deltaTime);
	void Render();

	const TextureResourceManager* GetTextureManager() const { return &mTextureResourceManager; }
	const PixelShaderResourceManager* GetPixelShaderManager() const { return &mPResourceManager; }
	const VertexShaderResourceManager* GetVertexShaderManager() const { return &mVResourceManager; }
	const PrimitiveMeshResourceManager* GetPrimitiveMeshManager() const { return &mPrimitiveResourceManager; }

private:
	void DestroyInternal(GameObject* gameObject);
	void ProcessDestroyList();

	void InitializeResources(const tinyxml2::XMLNode* node);

	using GameObjectList = std::vector<GameObject*>;

	std::unique_ptr<GameObjectAllocator> mGameObjectAllocator;
	std::unique_ptr<GameObjectHandlePool> mGameObjectHandlePool;
	std::unique_ptr<GameObjectFactory> mGameObjectFactory;

	//Resource Managers
	VertexShaderResourceManager mVResourceManager;
	PixelShaderResourceManager mPResourceManager;
	TextureResourceManager mTextureResourceManager;
	PrimitiveMeshResourceManager mPrimitiveResourceManager;

	GameObjectList mUpdateList;
	GameObjectList mDestroyList;
	bool mIsInitialized{ false };
	bool mUpdating{ false };
};
}//!namespace Engine
}//!namespace ZERO


#endif // !INCLUDED_ENGINE_WORLD_H
