#ifndef INCLUDED_GRAPHICS_DEPTHMAPNODE_H
#define INCLUDED_GRAPHICS_DEPTHMAPNODE_H

#include "SceneNode.h"
#include "DepthMap.h"
#include "Types.h"

namespace ZERO
{
	namespace Graphics
	{
		class DepthMapNode : public SceneNode
		{
		public:
			DepthMapNode();
			~DepthMapNode();


			void OnPreRender()			   override;
			void OnPostRender()			   override;

			void Initialize(uint32_t index);
			void Terminate();

			void SetDepthMap(DepthMap* dm) { mpDepthMap = dm; }

			void SetHasTexture(bool hastexture) { mUseAsTexture = hastexture; }

		protected:
			DepthMap *mpDepthMap;
			bool mUseAsTexture;
			uint32_t mIndex;



		};
	}
}


#endif // !INCLUDED_GRAPHICS_DEPTHMAPNODE_H

