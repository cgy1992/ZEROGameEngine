#ifndef INCLUDED_GRAPHICS_LIGHT
#define INCLUDED_GRAPHICS_LIGHT

#include <Math\Inc\ZMath.h>

namespace ZERO
{
namespace Graphics
{

	struct DirectionalLight
	{
		DirectionalLight()
			: ambient(Math::Vector4::White())
			, diffuse(Math::Vector4::White())
			, specular(Math::Vector4::White())
			, direction(Math::Vector3::ZAxis())
			, pad(0.0f)
		{}

		Math::Vector4	ambient;
		Math::Vector4	diffuse;
		Math::Vector4	specular;
		Math::Vector3	direction;
		float			pad;
	};

	struct PointLight
	{
		PointLight()
			: ambient(Math::Vector3::ZAxis(), 0.0f)
			, diffuse(Math::Vector4::White())
			, specular(Math::Vector4::White())
			, range(0.0f)
			, pad(0.0f)
		{}

		Math::Vector4	ambient;
		Math::Vector4	diffuse;
		Math::Vector4	specular;

		Math::Vector3	position;
		float			range;

		Math::Vector3	att;
		float			pad;
	};


	struct SpotLight
	{
		SpotLight()
			: ambient(Math::Vector3::ZAxis(), 0.0f)
			, diffuse(Math::Vector4::White())
			, specular(Math::Vector4::White())
			, direction(Math::Vector3::ZAxis())
			, range(0.0f)
			, pad(0.0f)
		{}

		Math::Vector4	ambient;
		Math::Vector4	diffuse;
		Math::Vector4	specular;

		Math::Vector3	position;
		float			range;

		Math::Vector3	direction;
		float			spot;

		Math::Vector3	att;
		float			pad;
	};
	

}//namespace Graphics
}//namespace ZERO


#endif //!INCLUDED_GRAPHICS_LIGHT
