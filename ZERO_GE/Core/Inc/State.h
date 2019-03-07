#ifndef INCLUDED_CORE_STATE_H
#define INCLUDED_CORE_STATE_H

namespace ZERO
{
namespace Core
{
class State
{
public:

	virtual ~State() {};
	virtual void Load() = 0;
	//Return the name of the scene that you are in the moment
	virtual std::string Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;

	//Getters and Setters
	void SetName(std::string name) { mName = name; }
	std::string GetName() const { return mName; }

private:
	std::string mName;
};
}//!namespace Core
}//!namespace ZERO




#endif //!INCLUDED_CORE_STATE_H
