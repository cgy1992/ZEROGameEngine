
#include "Precompiled.h"
#include "PixelShader.h"

using namespace ZERO;
using namespace ZERO::Graphics;

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

namespace
{
	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
}

PixelShader::PixelShader()
	:mPixelShader(nullptr)
	,mRasterizer(nullptr)
{}

PixelShader::~PixelShader()
{}

void PixelShader::Initialize(const wchar_t* filepath)
{
	/////////////////////////////////
	//Compile and create the vertex shader
	//D3DCOMPILE_DEBUG flag improves the shader debugging experience

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	/////////////////////////////////
	//Compile and create Pixel shader

	HRESULT hr = D3DCompileFromFile
	(
		filepath,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS",
		"ps_5_0",
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);

	ASSERT(SUCCEEDED(hr), "Failed to compile shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	SafeRelease(errorBlob);

	auto gs = Graphics::GraphicsSystem::Get();
	//Create the pixel shader
	gs->GetDevice()->CreatePixelShader
	(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader
	);

	

	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerState.CullMode = D3D11_CULL_FRONT;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = true;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;
	gs->GetDevice()->CreateRasterizerState(&rasterizerState, &mRasterizer);

	SafeRelease(shaderBlob);
}

void PixelShader::Initialize(const wchar_t* shader, const char* entryPoint, const char* shaderModel)
{
	/////////////////////////////////
	//Compile and create the vertex shader
	//D3DCOMPILE_DEBUG flag improves the shader debugging experience

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	/////////////////////////////////
	//Compile and create Pixel shader

	HRESULT hr = D3DCompileFromFile
	(
		shader,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		shaderModel,
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);

	ASSERT(SUCCEEDED(hr), "Failed to compile shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	SafeRelease(errorBlob);

	auto gs = Graphics::GraphicsSystem::Get();
	//Create the pixel shader
	gs->GetDevice()->CreatePixelShader
	(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader
	);



	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerState.CullMode = D3D11_CULL_FRONT;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = true;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;
	gs->GetDevice()->CreateRasterizerState(&rasterizerState, &mRasterizer);

	SafeRelease(shaderBlob);
}

void PixelShader::Terminate()
{
	SafeRelease(mPixelShader);
	SafeRelease(mRasterizer);
}

void PixelShader::Bind()
{
	auto gs = Graphics::GraphicsSystem::Get();
	ID3D11DeviceContext* context = gs->GetContext();
	context->PSSetShader(mPixelShader, nullptr, 0);
}