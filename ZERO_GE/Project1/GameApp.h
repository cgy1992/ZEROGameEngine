#ifndef INCLUDED_GAMEAPP_HEADER
#define INCLUDED_GAMEAPP_HEADER

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <External/ImGui/Inc/imgui.h>


using namespace ZERO::Graphics;

enum class ShapeMode
{
	HEART,
	TRIFORCE,
	STAR,
	SURPRISE
};


class GameApp : public ZERO::Core::Application
{
public:
	GameApp();
	~GameApp() override;

private:
	void OnInitialize() override;
	void OnTerminate() override;
	void OnUpdate() override;

	void InitializeBuffers();
	void ChangeMode();
	void RenderShape();

	ZERO::Core::Window mWindow;
	ZERO::Core::Timer mTimer;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mVertexBufferTriforce;
	ID3D11Buffer* mVertexBufferStar;
	ID3D11Buffer* mVertexBufferSurprise;
	ShapeMode shape;
	PixelShader mPixelShader;
	VertexShader mVertexShader;
};




#endif // !INCLUDED_GAMEAPP_HEADER
