//====================================================================================================
// Filename:	VertexShader.h
// Created by:	Erick Tavares
//====================================================================================================


#ifndef INCLUDED_GRAPHICS_VERTEXSHADER_H
#define INCLUDED_GRAPHICS_VERTEXSHADER_H

#include <Graphics\Inc\GraphicsSystem.h>



namespace ZERO{
namespace Graphics{

	

	class VertexShader
	{
	public:
		VertexShader();
		~VertexShader();

		void Initialize(const wchar_t* filepath, const char* entryPoint, const char* shaderModel, uint32_t vertexFormat);
		void Terminate();
		void Bind();


	private:
		ID3D11InputLayout* mInputLayout;
		ID3D11VertexShader* mVertexShader;
	};

} //Namespace Graphics
} //Namespace ZERO

#endif // !

