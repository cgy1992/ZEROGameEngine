#ifndef INCLUDED_ENGINE_RESOURCEMANAGER_H
#define INCLUDED_ENGINE_RESOURCEMANAGER_H


namespace ZERO
{
namespace Engine
{
template<class Resource>
class ResourceManager
{
	using Resources = std::map<std::string, std::unique_ptr<Resource>>;
public:
	ResourceManager() {};
	~ResourceManager() {};

	Resource* GetResource(std::string resourceID) const;
	virtual void Terminate() {}
	virtual std::string LoadResource(std::string path) { return std::string("Empty"); }

protected:
	Resources mResources;

};

template<class Resource>
Resource* ResourceManager<Resource>::GetResource(std::string resourceID) const
{
	return mResources.at(resourceID).get();
}


}
}


#endif // !INCLUDED_ENGINE_RESOURCEMANAGER_H
