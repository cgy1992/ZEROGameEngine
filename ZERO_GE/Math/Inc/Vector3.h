#ifndef INCLUDED_MATH_VECTOR3_H
#define INCLUDED_MATH_VECTOR3_H

namespace ZERO
{
namespace Math
{

struct Vector3
{
	float x, y, z;

	Vector3 operator+(Vector3 v) const { return { x + v.x, y + v.y, z + v.z }; }
};

} //namespace Math
} //namespace ZERO




#endif // !INCLUDED_MATH_VECTOR3_H
