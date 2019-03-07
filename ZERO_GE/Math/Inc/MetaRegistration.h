#ifndef INCLUDED_MATH_METAREGISTRATION_H
#define INCLUDED_MATH_METAREGISTRATION_H



namespace ZERO
{
namespace Math
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Quaternion;

}//!namespace ZERO
}//!namespace Math

META_TYPE_DECLARE(ZERO::Math::Vector2);
META_TYPE_DECLARE(ZERO::Math::Vector3);
META_TYPE_DECLARE(ZERO::Math::Vector4);
META_TYPE_DECLARE(ZERO::Math::Quaternion);






#endif // !INCLUDED_MATH_METAREGISTRATION_H
