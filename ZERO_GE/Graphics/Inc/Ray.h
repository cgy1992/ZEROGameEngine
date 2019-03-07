#ifndef INCLUDED_GRAPHICS_RAY
#define INCLUDED_GRAPHICS_RAY

#include <Graphics/Inc/Camera.h>
namespace ZERO
{
namespace Graphics
{
class Ray
{
public:
	static Math::Vector3 RayCast();


private:
	Math::Vector3 mOrigin;
	Math::Vector3 mDirection;
	Math::Vector3 mEnd;
};
}
}




#endif // !INCLUDED_GRAPHICS_RAY

