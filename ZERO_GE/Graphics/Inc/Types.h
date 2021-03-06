#ifndef INCLUDED_GRAPHICS_TYPES_H
#define INCLUDED_GRAPHICS_TYPES_H


namespace ZERO
{
namespace Graphics
{

	enum class ShaderStage
	{
		VS = 0x1 << 0,
		GS = 0x1 << 1,
		PS = 0x1 << 2
	};
	enum class CullMode
	{
		Front,
		Back,
		None
	};

	enum class FillMode
	{
		Solid,
		Wireframe
	};

	enum class ColorFormat
	{
		RGBA_U8,
		RGBA_U32,
		RGBA_F16,
		R_S32,
		R_F16
	};

}
}




#endif // !INCLUDED_GRAPHICS_TYPES_H

