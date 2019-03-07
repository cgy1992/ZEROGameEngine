#ifndef INCLUDED_SCENE_INPUTNODE_H
#define INCLUDED_SCENE_INPUTNODE_H

#include "SceneNode.h"
#include "ConstantBuffer.h"



namespace ZERO
{
namespace Graphics
{

	class InputNode : public SceneNode
	{
	public:
		enum class BindType { VS, PS, GS, CS, VSPS, ALL };

		struct ConstantBuffer
		{
			Math::Vector4 inputs;
		};

		InputNode();
		virtual ~InputNode();

		void Initialize(BindType type = BindType::VSPS, uint32_t bindIndex = 1);
		void Terminate();

		void SetInputs(Math::Vector4 inputs);
		void SetInputs(float i1, float i2, float i3, float i4);
		void SetInputs(Math::Vector3 inputs, float inpt);
		void SetBindType(BindType type) { mType = type; }

		Math::Vector4 GetInputs() const { return mInputs; }
		Math::Vector4& GetInputs() { return mInputs; }


	protected:
		virtual void OnRender();
		virtual void OnPostRender();

	protected:
		TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

		Math::Vector4 mInputs;
		uint32_t mBindIndex;
		BindType mType;
	};
}
}


#endif //INCLUDED_SCENE_INPUTNODE_H
