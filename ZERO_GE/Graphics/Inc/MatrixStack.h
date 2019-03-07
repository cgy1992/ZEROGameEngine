#ifndef INCLUDED_GRAPHICS_MATRIXSTACK_HEADER
#define INCLUDED_GRAPHICS_MATRIXSTACK_HEADER

namespace ZERO
{
namespace Graphics
{
class MatrixStack
{
public:
	MatrixStack();
	~MatrixStack();

	void PushMatrix(Math::Matrix4& matrix);
	void PopMatrix();

	Math::Matrix4 GetMatrixTranspose() const;

private:
	std::stack<Math::Matrix4> mMatrixStack;
};
}
}


#endif // !1
