//====================================================================================================
// Filename:	PixelShader.h
// Created by:	Erick Tavares
//====================================================================================================
#ifndef INCLUDED_GRAPHICS_PIXELSHADER_H
#define INCLUDED_GRAPHICS_PIXELSHADER_H

#include <Graphics\Inc\GraphicsSystem.h>

namespace ZERO{
namespace Graphics{

	class PixelShader
	{
	public:
		PixelShader();
		~PixelShader();

		void Initialize(const wchar_t* filepath);
		void Initialize(const wchar_t* shader, const char* entryPoint, const char* shaderModel);
		void Terminate();
		void Bind();


	private:
		ID3D11PixelShader* mPixelShader;
		ID3D11RasterizerState* mRasterizer;
	};

} //Namespace Graphics
} //Namespace ZERO



#endif // !INCLUDED_GRAPHICS_PIXELSHADER_H

