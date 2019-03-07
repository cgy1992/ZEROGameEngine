#ifndef INCLUDED_ENGINE_TEXTURECOMPONENT_H
#define INCLUDED_ENGINE_TEXTURECOMPONENT_H

#include "Component.h"

namespace ZERO
{
namespace Engine
{

class TextureComponent : public Component
{
public:
	META_CLASS_DECLARE
	TextureComponent();
	~TextureComponent() override;

	void Initialize() override;
	void Render() override;
	void Terminate() override;
	

private:
	std::string mTextureName;
	int mBindIndex;
};
}//!namespace Engine
}//!namespace ZERO

#endif // !INCLUDED_ENGINE_TEXTURECOMPONENT_H

