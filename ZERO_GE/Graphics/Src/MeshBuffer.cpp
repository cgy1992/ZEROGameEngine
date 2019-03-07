#include "Precompiled.h"
#include "MeshBuffer.h"
#include "Mesh.h"
#include "SkinMesh.h"

using namespace ZERO;
using namespace ZERO::Graphics;

MeshBuffer::MeshBuffer()
	:mVertexBuffer(nullptr)
	, mIndexBuffer(nullptr)
	, mVertexSize(0)
	, mVertexCount(0)
	, mIndexCount(0)
	, mMode(0)
{}


MeshBuffer::~MeshBuffer()
{
	ASSERT(mVertexBuffer == nullptr, "[MeshBuffer] Vertex Buffer not released");
	ASSERT(mIndexBuffer == nullptr, "[MeshBuffer] Index Buffer not released");
}

void MeshBuffer::Initialize(const Mesh& mesh)
{
	Initialize(	mesh.GetVertices(), 
				sizeof(Vertex), 
				mesh.GetVertexCount(), 
				mesh.GetIndices(), 
				mesh.GetIndicesCount());
}

void MeshBuffer::Initialize(const SkinMesh& mesh)
{
	Initialize(mesh.GetVertices(),
		sizeof(BoneVertex),
		mesh.GetVertexCount(),
		mesh.GetIndices(),
		mesh.GetIndicesCount());
}

void MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount)
{

	mVertexSize = vertexSize;
	mVertexCount = vertexCount;
	mIndexCount = indexCount;


	auto graphicsSystem = Graphics::GraphicsSystem::Get();

	////////////////////////////////
	//Create and fill vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	D3D11_SUBRESOURCE_DATA initData = {};

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	bufferDesc.ByteWidth = mVertexSize * mVertexCount;
	initData.pSysMem = vertices;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	

	//Index Buffer
	///////////////////////////////////////////////////
	//Create and fill Index buffer
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(uint32_t) * mIndexCount;

	initData.pSysMem = indices;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);


}


void MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount)
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	mVertexSize = vertexSize;
	mVertexCount = vertexCount;

	////////////////////////////////
	//Create and fill vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	D3D11_SUBRESOURCE_DATA initData = {};

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	bufferDesc.ByteWidth = mVertexSize * mVertexCount;
	initData.pSysMem = vertices;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
}


void MeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);
}

void MeshBuffer::Render()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	ID3D11DeviceContext* context = graphicsSystem->GetContext();

	//Set vertex buffer
	UINT stride = mVertexSize;
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//Set primitive topology
	switch (mMode)
	{
	case 0:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case 1:
		context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	default:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}
	

	//Check if we are using index buffer
	if (mIndexBuffer != nullptr)
	{
		//set Index Buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//Draw Index Mesh
		context->DrawIndexed(mIndexCount, 0, 0);
	}
	else
	{
		//Draw mesh
		context->Draw(mVertexCount, 0);
	}

}