

//====================================================================================================
// Includes
//====================================================================================================
#include "Precompiled.h"
#include "InputNode.h"


using namespace ZERO;
using namespace ZERO::Graphics;
//====================================================================================================
// Class Definitions
//====================================================================================================

InputNode::InputNode()
	: SceneNode()
	, mBindIndex(0)
	, mType(BindType::VSPS)
	, mInputs(Math::Vector4::White())
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

InputNode::~InputNode()
{
}

//----------------------------------------------------------------------------------------------------

void InputNode::Initialize(BindType type, uint32_t bindIndex)
{
	mConstantBuffer.Initialize();
	mBindIndex = bindIndex;
	mType = type;
	mInputs = Math::Vector4::White();
}

//----------------------------------------------------------------------------------------------------

void InputNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void InputNode::OnRender()
{
	ConstantBuffer constants;

	constants.inputs.x = mInputs.x;
	constants.inputs.y = mInputs.y;
	constants.inputs.z = mInputs.z;
	constants.inputs.w = mInputs.w;

	mConstantBuffer.Set(constants);

	switch (mType)
	{
	case BindType::VS:
		mConstantBuffer.BindVS(mBindIndex);
		break;
	case BindType::PS:
		mConstantBuffer.BindPS(mBindIndex);
		break;
	case BindType::GS:
		mConstantBuffer.BindGS(mBindIndex);
		break;
	case BindType::CS:
		mConstantBuffer.BindCS(mBindIndex);
		break;
	case BindType::VSPS:
		mConstantBuffer.BindVS(mBindIndex);
		mConstantBuffer.BindPS(mBindIndex);
		break;
	case BindType::ALL:
		mConstantBuffer.BindVS(mBindIndex);
		mConstantBuffer.BindPS(mBindIndex);
		mConstantBuffer.BindGS(mBindIndex);
		mConstantBuffer.BindCS(mBindIndex);
		break;
	default:
		break;
	}
	

}

void InputNode::OnPostRender()
{

	switch (mType)
	{
	case BindType::VS:
		mConstantBuffer.UnbindVS(mBindIndex);
		break;
	case BindType::PS:
		mConstantBuffer.UnbindPS(mBindIndex);
		break;
	case BindType::GS:
		mConstantBuffer.UnbindGS(mBindIndex);
		break;
	case BindType::CS:
		mConstantBuffer.UnbindCS(mBindIndex);
		break;
	case BindType::VSPS:
		mConstantBuffer.UnbindVS(mBindIndex);
		mConstantBuffer.UnbindPS(mBindIndex);
		break;
	case BindType::ALL:
		mConstantBuffer.UnbindVS(mBindIndex);
		mConstantBuffer.UnbindPS(mBindIndex);
		mConstantBuffer.UnbindGS(mBindIndex);
		mConstantBuffer.UnbindCS(mBindIndex);
		break;
	default:
		break;
	}
}

void InputNode::SetInputs(Math::Vector4 inputs) { mInputs = inputs; }

void InputNode::SetInputs(float i1, float i2, float i3, float i4)
{
	mInputs = { i1, i2, i3, i4 };
}

void InputNode::SetInputs(Math::Vector3 inputs, float inpt)
{
	mInputs = { inputs, inpt };
}