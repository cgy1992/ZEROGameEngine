#ifndef INCLUDED_GRAPHICS_KEYFRAME_H
#define INCLUDED_GRAPHICS_KEYFRAME_H

namespace ZERO
{
namespace Graphics
{
	template<typename T>
	struct Keyframe
	{
	public:
		float timer;
		void SetValue(T v) { value = v; }
		T GetValue() const { return value; }
	private:
		T value;
	};
}// !namespace Graphics
}// !namespace ZERO

#endif // !INCLUDED_GRAPHICS_KEYFRAME_H

