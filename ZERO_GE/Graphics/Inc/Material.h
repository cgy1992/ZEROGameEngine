#ifndef INCLUDED_GRAPHICS_MATERIAL
#define INCLUDED_GRAPHICS_MATERIAL

#include <Math\Inc\ZMath.h>

namespace ZERO
{
namespace Graphics
{

	struct Material
	{
		Material()
			: ambient(Math::Vector4::White())
			, diffuse(Math::Vector4::White())
			, specular(Math::Vector4::White())
			, emissive(Math::Vector4::White())
			, power(1.0f)
		{}

		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular;
		Math::Vector4 emissive;
		float power;

		int hasDiffuseMap{ 0 };
		int hasSpecularMap{ 0 };
		int hasNormalMap{ 0 };
		int hasDisplacementMap{ 0 };
	};


}//namespace Graphics
}//namespace ZERO


#endif //!INCLUDED_GRAPHICS_LIGHT
