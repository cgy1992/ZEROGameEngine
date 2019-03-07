#include "GameApp.h"
#include "Graphics\Inc\Gui.h"

using namespace ZERO;


namespace //Internal Linkage
{
	struct SimpleVertex
	{
		Math::Vector3 position;
		Math::Vector4 color;
	};

	const SimpleVertex kVertices[] =
	{
		//HEART LEFT SIDE
		{ Math::Vector3(-0.34f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.34f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.34f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.34f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.51f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.34f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, -0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.51f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(-0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-0.17f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, -0.68f, 0.0f), Math::Vector4::Red() },


		//HEART RIGHT SIDE
		{ Math::Vector3 (0.0f, -0.68f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, -0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, -0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, -0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.0f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.51f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.17f, -0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.34f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.34f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.34f, 0.0f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.34f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(0.17f, 0.34f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.17f, 0.51f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.34f, 0.34f, 0.0f), Math::Vector4::Red() },

		{ Math::Vector3(-10.0f, -1.0f, 0.0f),Math::Vector4::Black() },
		{ Math::Vector3(0.0f, 10.0f, 0.0f),Math::Vector4::Black() },
		{ Math::Vector3(10.0f, -1.0f, 0.0f),Math::Vector4::Black() },
	};

	const SimpleVertex kVerticesTriforce[] =
	{
		{ Math::Vector3(-0.17f, 0.0f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.0f, 0.51f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.17f, 0.0f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-0.34f, -0.51f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(-0.17f, 0.0f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.0f, -0.51f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(0.0f, -0.51f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.17f, 0.0f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.34f, -0.51f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-10.0f, -1.0f, 0.0f),{ 0.2f, 0.7f, 0.2f, 1.0f } },
		{ Math::Vector3(0.0f, 10.0f, 0.0f),{ 0.2f, 0.7f, 0.2f, 1.0f } },
		{ Math::Vector3(10.0f, -1.0f, 0.0f),{ 0.2f, 0.7f, 0.2f, 1.0f } },

	};

	const SimpleVertex kVerticesStar[] =
	{
		{ Math::Vector3(-0.68f, 0.17f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(-0.17f,0.17f,0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(-0.34f, -0.17f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.0f, 0.68f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(0.17f,0.17f,0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.68f, 0.17f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(0.34f, -0.17f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(0.0f, -0.34f,0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.34f, -0.17f, 0.0f),Math::Vector4::Yellow() },
		{ Math::Vector3(0.51f, -0.68f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		
		{ Math::Vector3(-0.51f, -0.68f, 0.0f),{ 0.9f, 0.8f, 0.2f, 1.0f } },
		{ Math::Vector3(-0.34f, -0.17f, 0.0f),Math::Vector4::Yellow() },
		{ Math::Vector3(0.0f, -0.34f,0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-0.34f, -0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(-0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3( 0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(0.0f, -0.34f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.17f, 0.17f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.34f, -0.17f, 0.0f), Math::Vector4::Yellow() },

		{ Math::Vector3(-10.0f, -1.0f, 0.0f),Math::Vector4::Black() },
		{ Math::Vector3(0.0f, 10.0f, 0.0f),Math::Vector4::Black() },
		{ Math::Vector3(10.0f, -1.0f, 0.0f),Math::Vector4::Black() },

		

	};

	const SimpleVertex kVerticesSurprise[] =
	{
		{ Math::Vector3(-0.81f, -1.0f, 0.0f), {0.3f, 0.3f, 0.4f, 1.0f } },
		{ Math::Vector3(-0.34f, 0.51f, 0.0f),{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ Math::Vector3(0.10f, -1.0f, 0.0f),{ 0.3f, 0.3f, 0.4f, 1.0f } },

		{ Math::Vector3(-0.64f, -1.0f, 0.0f),{ 0.3f, 0.3f, 0.4f, 1.0f } },
		{ Math::Vector3(0.0f, 0.68f, 0.0f),{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ Math::Vector3(0.64f, -1.0f, 0.0f),{ 0.3f, 0.3f, 0.4f, 1.0f } },

		{ Math::Vector3(-0.30f, -1.0f, 0.0f),{ 0.3f, 0.3f, 0.4f, 1.0f } },
		{ Math::Vector3(0.42f, 0.42f, 0.0f),{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ Math::Vector3(0.94f, -1.0f, 0.0f),{ 0.3f, 0.3f, 0.4f, 1.0f } },

		{ Math::Vector3(-10.0f, -1.0f, 0.0f),{ 0.3f, 0.9f, 1.0f, 1.0f } },
		{ Math::Vector3(0.0f, 10.0f, 0.0f),{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ Math::Vector3(10.0f, -1.0f, 0.0f),{ 0.3f, 0.9f, 1.0f, 1.0f } },
	};
	const int KVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	const int KVertexCountStar = sizeof(kVerticesStar) / sizeof(kVerticesStar[0]);
	const int KVertexCountTriforce = sizeof(kVerticesTriforce) / sizeof(kVerticesTriforce[0]);
	const int KVertexCountSurprise = sizeof(kVerticesSurprise) / sizeof(kVerticesSurprise[0]);


}


GameApp::GameApp()
	: mVertexBuffer	(nullptr)
	, mVertexBufferStar(nullptr)
	, mVertexBufferTriforce(nullptr)
	, mVertexBufferSurprise(nullptr)
	, shape(ShapeMode::HEART)
{
	
}

GameApp::~GameApp()
{

}

void GameApp::OnInitialize()
{
	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 720);
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Gui::Initialize(mWindow.GetWindowHandle());
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();

	InitializeBuffers();

	mVertexShader.Initialize(L"../Assets/Shaders/DoColor.fx", "VS", "vs_5_0", Graphics::VertexPC::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/DoColor.fx");
	mTimer.Initialize();
}

void GameApp::OnTerminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	SafeRelease(mVertexBuffer);
	SafeRelease(mVertexBufferStar);
	SafeRelease(mVertexBufferTriforce);
	SafeRelease(mVertexBufferSurprise);

	Gui::Terminate();
	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	mTimer.Update();
	float dt = mTimer.GetElapsedTime();
	float velocity = 10.0f;
	float rotVelocity = 10.0f;
	Input::InputSystem* is = Input::InputSystem::Get();
	is->Update();

	

	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

	if (is->IsKeyPressed(Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}

	ChangeMode();


	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	//Bind the input layout, vertex shader and pixel shader
	ID3D11DeviceContext* context = graphicsSystem->GetContext();
	mVertexShader.Bind();
	mPixelShader.Bind();

	RenderShape();

	graphicsSystem->EndRender();
}

void GameApp::InitializeBuffers()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();

	////////////////////////////////
	//Create and fill vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};

	//Heart
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * KVertexCount;
	initData.pSysMem = kVertices;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);

	//Triforce
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * KVertexCountTriforce;
	initData.pSysMem = kVerticesTriforce;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBufferTriforce);

	//Star
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * KVertexCountStar;
	initData.pSysMem = kVerticesStar;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBufferStar);

	//Surprise
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * KVertexCountSurprise;
	initData.pSysMem = kVerticesSurprise;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBufferSurprise);
}

void GameApp::ChangeMode()
{

	if (GetAsyncKeyState(VK_F1))
	{
		shape = ShapeMode::HEART;
	}
	if (GetAsyncKeyState(VK_F2))
	{
		shape = ShapeMode::TRIFORCE;
	}
	if (GetAsyncKeyState(VK_F3))
	{
		shape = ShapeMode::STAR;
	}
	if (GetAsyncKeyState(VK_F4))
	{
		shape = ShapeMode::SURPRISE;
	}
}


void GameApp::RenderShape()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	ID3D11DeviceContext* context = graphicsSystem->GetContext();
	
	//Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	switch (shape)
	{
	case ShapeMode::HEART:
		context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		//Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Draw mesh
		context->Draw(KVertexCount, 0);
		break;
	case ShapeMode::TRIFORCE:
		context->IASetVertexBuffers(0, 1, &mVertexBufferTriforce, &stride, &offset);
		//Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Draw mesh
		context->Draw(KVertexCountTriforce, 0);
		break;
	case ShapeMode::STAR:
		context->IASetVertexBuffers(0, 1, &mVertexBufferStar, &stride, &offset);
		//Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Draw mesh
		context->Draw(KVertexCountStar, 0);
		break;
	case ShapeMode::SURPRISE:
		context->IASetVertexBuffers(0, 1, &mVertexBufferSurprise, &stride, &offset);
		//Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Draw mesh
		context->Draw(KVertexCountSurprise, 0);
		break;
	default:
		break;
	}
}
//Homework:
//Initialize 3 vertexBuffers and initialize them with the following:
//1)Triforce
//2)Heart
//3)Star
//4)Surprise
//
//Use this code below to switch between them:
// if(GetAsyncKeyState(VK_F1/VK_F2/VK_F3))
//
//Add vertex shader and pixel shader classes in graphics.
//
//Graphics::VertexShader mVertexShader
//

//class VertexShader
//	-Initialize()/Terminate()
//	-Bind()
