//====================================================================================================
// Filename:	Texture.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_GRAPHICS_TEXTURE_H
#define INCLUDED_GRAPHICS_TEXTURE_H
namespace ZERO
{
namespace Graphics
{

class Texture
{
public:
	enum class TextureType { DiffuseMap, SpecularMap, DisplacementMap, NormalMap };

	Texture();
	~Texture();

	void Initialize(const char* filename, uint32_t bindIndex = 0 );
	void Initialize(const void* data, uint32_t width, uint32_t height, uint32_t bindIndex = 0);
	void Terminate();

	void SetTextureType(TextureType type) { mType = type; }
	TextureType GetTextureType() const { return mType; }

	void SetBindIndex(uint32_t bindIndex) { mBindIndex = bindIndex; }

	void BindVS() const;
	void BindPS() const;

	void UnbindVS() const;
	void UnbindPS() const;

private:
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	friend class SpriteRenderer;
	TextureType mType;
	ID3D11ShaderResourceView* mShaderResourceView;
	uint32_t mBindIndex;
};

} // namespace Graphics
} // namespace ZERO
#endif // #ifndef INCLUDED_GRAPHICS_TEXTURE_H