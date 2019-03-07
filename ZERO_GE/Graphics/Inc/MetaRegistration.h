#ifndef INCLUDED_GRAPHICS_METAREGISTRATION
#define INCLUDED_GRAPHICS_METAREGISTRATION

namespace ZERO
{
namespace Graphics
{
namespace Meta
{
	struct Int4
	{
		int a;
		int b;
		int c;
		int d;
	};

	
	void MetaRegister();
	
}
}
}

META_TYPE_DECLARE(ZERO::Graphics::Meta::Int4)

#endif // !INCLUDED_GRAPHICS_METAREGISTRATION
