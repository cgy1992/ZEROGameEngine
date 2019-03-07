#include "Precompiled.h"
#include "World.h"
#include "XMLReader.h"

using namespace ZERO;
using namespace ZERO::Engine;

using namespace ZERO::Engine::XMLReader;
using namespace tinyxml2;

void World::Initialize(uint32_t capacity)
{
	ASSERT(!mIsInitialized, "[World] World is already initialized");
	mGameObjectAllocator = std::make_unique<GameObjectAllocator>(capacity);
	mGameObjectHandlePool = std::make_unique<GameObjectHandlePool>(capacity);
	mGameObjectFactory = std::make_unique<GameObjectFactory>(*mGameObjectAllocator);

	mPrimitiveResourceManager.LoadResource("");

	mIsInitialized = true;
}

void World::Terminate()
{
	if (!mIsInitialized)
	{
		return;
	}

	ASSERT(!mUpdating, "[World] Cannot terminate world during update.");

	mUpdating = true;

	std::for_each(mUpdateList.begin(), mUpdateList.end(), [this](GameObject* gameObject)
	{
		Destroy(gameObject->GetHandle());
	});

	mUpdating = false;
	mUpdateList.clear();

	//Processing Destroy list
	ProcessDestroyList();

	mGameObjectFactory.reset();
	mGameObjectHandlePool.reset();
	mGameObjectAllocator.reset();

	mIsInitialized = false;
}

void World::LoadLevel(const char* levelFileName)
{
	tinyxml2::XMLDocument doc;
	XMLError er = doc.LoadFile(levelFileName);

	XMLNode* pRoot = doc.FirstChild();
	ASSERT(pRoot, "[XMLError] Could not read xml file.");

	if (strcmp(pRoot->Value(), "Level") == 0)
	{
		const XMLElement* pResource = pRoot->FirstChildElement("Resources");
		if (pResource != nullptr)
		{
			const XMLNode* nextCompNode = pResource->FirstChild();
			while (nextCompNode != nullptr)
			{
				InitializeResources(nextCompNode);
				nextCompNode = nextCompNode->NextSibling();
			}
		}
		const XMLElement* pGameObjects = pRoot->FirstChildElement("GameObjects");
		if (pGameObjects != nullptr)
		{
			const XMLNode* nextGameObject = pGameObjects->FirstChild();
			while (nextGameObject != nullptr)
			{
				const char* path = nextGameObject->FirstChild()->FirstChild()->Value();
				const char* name = nextGameObject->ToElement()->FirstAttribute()->Value();
				GameObjectHandle handle = Create(path, name);

				const XMLNode* nextComponent = nextGameObject->FirstChild()->NextSibling();
				while (nextComponent != nullptr)
				{
					const char* componentName = nextComponent->Value();
					const ZERO::Core::Meta::MetaClass* metaclass = ZERO::Core::Meta::MetaRegistry::FindMetaClass(nextComponent->Value());
					auto component = handle.Get()->GetComponentByMetaClass(metaclass);
					VERIFY(XMLReader::Read(component, metaclass, nextComponent->FirstChild()), "Failed to read %s", componentName);
					nextComponent = nextComponent->NextSibling();
				}
				
				nextGameObject = nextGameObject->NextSibling();
			}

		}
	}

	
}

void World::InitializeResources(const XMLNode* node)
{
	const char* componentName = node->Value();

	if (strcmp(componentName, "VertexShader") == 0)
	{
		std::string path(node->FirstChild()->Value());
		mVResourceManager.LoadResource(path);
	}
	else if (strcmp(componentName, "PixelShader") == 0)
	{
		std::string path(node->FirstChild()->Value());
		mPResourceManager.LoadResource(path);
	}
	else if (strcmp(componentName, "Texture") == 0)
	{
		std::string path(node->FirstChild()->Value());
		mTextureResourceManager.LoadResource(path);
	}
}




GameObjectHandle World::Create(const char* templateFileName, const char* name)
{
	auto gameObject = mGameObjectFactory->Create(templateFileName);
	ASSERT(gameObject != nullptr, "[World] Failed to create game object from template %s", templateFileName);

	//Register with the handle pool
	auto handle = mGameObjectHandlePool->Register(gameObject);

	//Initialize
	gameObject->mWorld = this;
	gameObject->mHandle = handle;
	gameObject->mName = name;
	gameObject->Initialize();

	//Add GameObject to the update list
	mUpdateList.push_back(gameObject);

	return handle;
}

GameObjectHandle World::Find(const char* name)
{
	GameObjectHandle go;
	for (auto gameObject : mUpdateList)
	{
		if (gameObject->GetName().compare(name) == 0)
		{
			return gameObject->GetHandle();
		}
	}

	return go;
}

void World::Destroy(GameObjectHandle handle)
{
	if (!handle.IsValid())
	{
		return;
	}

	//Cache the pointer and unregister with the handle pool
	GameObject* gameObject = handle.Get();
	mGameObjectHandlePool->Unregister(handle);

	//Check if we can destroy it now
	if (!mUpdating)
	{
		DestroyInternal(gameObject);
	}
	else
	{
		mDestroyList.push_back(gameObject);
	}
}

void World::Update(float deltaTime)
{

	ASSERT(!mUpdating, "[World] Already updating the world.");

	//Lock the Update list
	mUpdating = true;

	//Re-compute in case new objects are added to the update 
	//list during iteration
	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		GameObject* gameObject = mUpdateList[i];
		if (gameObject->GetHandle().IsValid())
		{
			gameObject->Update(deltaTime);
		}
	}

	//Unlock the update list
	mUpdating = false;

	//Now can safely destroy the object
	ProcessDestroyList();
}

void World::Render()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}


void World::DestroyInternal(GameObject* gameObject)
{
	ASSERT(!mUpdating, "[World] Cannot destroy game objects during update.");

	//Cleaning resources
	mVResourceManager.Terminate();
	mPResourceManager.Terminate();
	mTextureResourceManager.Terminate();
	mPrimitiveResourceManager.Terminate();

	if (gameObject == nullptr)
	{
		return;
	}

	auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);

	if (iter != mUpdateList.end())
	{
		mUpdateList.erase(iter);
	}

	gameObject->Terminate();

	mGameObjectFactory->Destroy(gameObject);
}

void World::ProcessDestroyList()
{
	for (auto objectToDestroy : mDestroyList)
	{
		DestroyInternal(objectToDestroy);
	}
}