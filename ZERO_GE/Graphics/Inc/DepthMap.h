#ifndef INCLUDED_GRAPHICS_DEPTHMAP_H
#define INCLUDED_GRAPHICS_DEPTHMAP_H
#include "Types.h"

namespace ZERO
{
namespace Graphics
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class DepthMap
{
public:
	DepthMap();
	~DepthMap() {}

	DepthMap(const DepthMap&) = delete;
	DepthMap& operator=(const DepthMap&) = delete;

	void Initialize(uint32_t width, uint32_t height);
	void Terminate();

	void BeginRender();
	void EndRender();

	void BindTexture(uint32_t index);
	void UnbindTexture(uint32_t index);

	//void Copy(ID3D11Texture2D* texture);
private:

	ID3D11ShaderResourceView* mShaderResourceView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewport;

};
}// !namespace Graphics
}// !namespace ZERO

#endif // !INCLUDED_GRAPHICS_DEPTHMAP_H

