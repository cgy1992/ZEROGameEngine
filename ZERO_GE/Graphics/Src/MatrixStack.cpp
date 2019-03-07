#include "Precompiled.h"
#include "MatrixStack.h"


using namespace ZERO;
using namespace ZERO::Graphics;

MatrixStack::MatrixStack()
{}

MatrixStack::~MatrixStack()
{}

void MatrixStack::PushMatrix(Math::Matrix4& matrix)
{
	if (mMatrixStack.size() == 0)
	{
		mMatrixStack.push(matrix);
		return;
	}

	Math::Matrix4 m = matrix * mMatrixStack.top();
	mMatrixStack.push(m);

}

void MatrixStack::PopMatrix()
{
	mMatrixStack.pop();
}

Math::Matrix4 MatrixStack::GetMatrixTranspose() const
{
	return Math::Transpose(mMatrixStack.top());
}