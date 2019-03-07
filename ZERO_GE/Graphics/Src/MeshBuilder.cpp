#include "Precompiled.h"

#include "MeshBuilder.h"

using namespace ZERO;
using namespace ZERO::Graphics;

MeshBuilder::MeshBuilder()
{}

MeshBuilder::~MeshBuilder()
{}

void MeshBuilder::CreateCube(Mesh& mesh)
{
	Vertex* kCube = new Vertex[24];
	Vertex kVertices[] = 
	{
		//FACE FRONT-----------------------------------------------------------------------------------------------------------------------------------------
		{ {-0.5f,  0.5f, -0.5f}	,{0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } }, //0
		{ { 0.5f,  0.5f, -0.5f}	,{0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f } }, //1
		{ { 0.5f, -0.5f, -0.5f}	,{0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 2.0f } }, //2
		{ {-0.5f, -0.5f, -0.5f}  ,{0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 2.0f } }, //3
		//---------------------------------------------------------------------------------------------------------------------------------------------------
		//FACE RIGHT-----------------------------------------------------------------------------------------------------------------------------------------				
		{ { 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, //4
		{ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {2.0f, 0.0f}}, //5
		{ { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {2.0f, 2.0f}}, //6
		{ { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 2.0f}}, //7
		//---------------------------------------------------------------------------------------------------------------------------------------------------
		//FACE BACK------------------------------------------------------------------------------------------------------------------------------------------
		{ { 0.5f,  0.5f, 0.5f},	{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //8
		{ {-0.5f,  0.5f, 0.5f},	{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {2.0f, 0.0f}}, //9
		{ {-0.5f, -0.5f, 0.5f},	{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {2.0f, 2.0f}}, //10
		{ { 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 2.0f}}, //11
		//---------------------------------------------------------------------------------------------------------------------------------------------------
		//FACE LEFT------------------------------------------------------------------------------------------------------------------------------------------
		{ {-0.5f,  0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, //12
		{ {-0.5f,  0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {2.0f, 0.0f}}, //13
		{ {-0.5f, -0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {2.0f, 2.0f}}, //14
		{ {-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 2.0f}}, //15
		//---------------------------------------------------------------------------------------------------------------------------------------------------
		//FACE TOP-------------------------------------------------------------------------------------------------------------------------------------------
		{ {-0.5f, 0.5f, -0.5f},	{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //16
		{ {-0.5f, 0.5f,  0.5f},	{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {2.0f, 0.0f}}, //17
		{ { 0.5f, 0.5f,  0.5f},	{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {2.0f, 2.0f}}, //18
		{ { 0.5f, 0.5f, -0.5f},	{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 2.0f}}, //19
		//---------------------------------------------------------------------------------------------------------------------------------------------------
		//FACE BOTTOM----------------------------------------------------------------------------------------------------------------------------------------
		{ {-0.5f, -0.5f,-0.5f}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //20
		{ { 0.5f, -0.5f,-0.5f}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {2.0f, 0.0f}}, //21
		{ { 0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {2.0f, 2.0f}}, //22
		{ {-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 2.0f}} //23
		//---------------------------------------------------------------------------------------------------------------------------------------------------
	};

	const int KVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);

	uint32_t* kCubeIndices = new uint32_t[36];
	uint32_t kIndices[] =
	{
		//Front
		0, 1, 2,
		0, 2, 3,
		//Right
		4, 5, 6,
		4, 6, 7,
		//Back
		9, 10, 11,
		9, 11, 8,
		//Left
		12, 13, 14,
		12, 14, 15,
		//Top
		16, 17, 19,
		19, 17, 18,
		//Bottom
		20, 21, 22,
		20, 22, 23
	};

	constexpr int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);

	mesh.Allocate(KVertexCount, kIndexCount);

	for (uint32_t i = 0; i < 24; ++i)
	{
		mesh.GetVertex(i) = kVertices[i];
	}

	for (uint32_t i = 0; i < 36; ++i)
	{
		mesh.GetIndex(i) = kIndices[i];
	}
}

void MeshBuilder::CreateSkyBox(Mesh& mesh)
{
	Vertex* kCube = new Vertex[24];
	Vertex kVertices[] =
	{
	//FACE FRONT-----------------------------------------------------------------------------------------------------------------------------------------
	{ { -0.5f,  0.5f, 0.0f }	,{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } }, //0
	{ { 0.5f,  0.5f, 0.0f }		,{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f } }, //1
	{ { 0.5f, -0.5f, 0.0f }		,{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 2.0f } }, //2
	{ { -0.5f, -0.5f, 0.0f }	,{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 2.0f } }, //3
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//FACE RIGHT-----------------------------------------------------------------------------------------------------------------------------------------				
	{ { 0.5f,  0.5f,  0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f } }, //4
	{ { 0.5f,  0.5f,  1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 2.0f, 0.0f } }, //5
	{ { 0.5f, -0.5f,  1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 2.0f, 2.0f } }, //6
	{ { 0.5f, -0.5f,  0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 2.0f } }, //7
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//FACE BACK------------------------------------------------------------------------------------------------------------------------------------------
	{ { 0.5f,  0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } }, //8
	{ { -0.5f,  0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f },{ 2.0f, 0.0f } }, //9
	{ { -0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f },{ 2.0f, 2.0f } }, //10
	{ { 0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 2.0f } }, //11
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//FACE LEFT------------------------------------------------------------------------------------------------------------------------------------------
	{ { -0.5f,  0.5f, 1.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f } }, //12
	{ { -0.5f,  0.5f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 2.0f, 0.0f } }, //13
	{ { -0.5f, -0.5f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 2.0f, 2.0f } }, //14
	{ { -0.5f, -0.5f, 1.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 2.0f } }, //15
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//FACE TOP-------------------------------------------------------------------------------------------------------------------------------------------
	{ { -0.5f, 0.5f,  0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } }, //16
	{ { -0.5f, 0.5f,  1.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 2.0f, 0.0f } }, //17
	{ { 0.5f, 0.5f,  1.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 2.0f, 2.0f } }, //18
	{ { 0.5f, 0.5f,  0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 2.0f } }, //19
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//FACE BOTTOM----------------------------------------------------------------------------------------------------------------------------------------
	{ { -0.5f, -0.5f, 0.0f },{ 0.0f, -1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } }, //20
	{ { 0.5f, -0.5f, 0.0f },{ 0.0f, -1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 2.0f, 0.0f } }, //21
	{ { 0.5f, -0.5f, 1.0f },{ 0.0f, -1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 2.0f, 2.0f } }, //22
	{ { -0.5f, -0.5f, 1.0f },{ 0.0f, -1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ 0.0f, 2.0f } } //23
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	};

	const int KVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);

	uint32_t* kCubeIndices = new uint32_t[36];
	uint32_t kIndices[] =
	{
		//Front
		2, 1, 0,
		3, 2, 0,
		//Right
		6, 5, 4,
		7, 6, 4,
		//Back
		11, 10, 9,
		8, 11, 9,
		//Left
		14, 13, 12,
		15, 14, 12,
		//Top
		19, 17, 16,
		18, 17, 19,
		//Bottom
		22, 21, 20,
		23, 22, 20
	};

	constexpr int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);

	mesh.Allocate(KVertexCount, kIndexCount);

	for (uint32_t i = 0; i < 24; ++i)
	{
		mesh.GetVertex(i) = kVertices[i];
	}

	for (uint32_t i = 0; i < 36; ++i)
	{
		mesh.GetIndex(i) = kIndices[i];
	}
}


//void MeshBuilder::CreateSkySphere(Mesh& mesh, uint32_t stacks, uint32_t slices)
//{
//	const uint32_t numVertices = ((stacks + 1) * (slices + 1));
//	const uint32_t numIndices = stacks * (6 * (slices));
//
//	mesh.Allocate(numVertices, numIndices);
//
//	const float kSliceStep = Math::kTwoPi / (stacks - 1); //calcula largura de um slice
//	const float kRingStep = Math::kPi / (slices - 1); // Calcula a largura de um ring
//													  // Fill vertex data
//	float uStep = 1.0f / (slices - 1);
//	float vStep = 1.0f / stacks;
//	uint32_t index = 0;
//
//	for (uint32_t j = 0; j <= slices; ++j)
//	{
//		const float phi = j * kRingStep;
//		for (uint32_t i = 0; i <= stacks; ++i)
//		{
//			float   theta = i * kSliceStep;
//			float   y = cos(phi);
//			float   r = sqrt(1.0f - (y * y));
//			float   s = sin(theta);
//			float   c = cos(theta);
//			float   x = r * c;
//			float	z = r * s;
//			Math::Vector3 p(x, y, z);
//			Math::Vector3 n(-x, -y, -z);
//			Math::Vector3 t(-s, 0.0f, c);
//			Math::Vector2 uv((i *uStep), (j*vStep));
//
//			if (i == stacks)
//			{
//				index = (j* stacks) + i;
//				mesh.GetVertex(index) = mesh.GetVertex(index - slices);
//				continue;
//			}
//
//			index = (j* stacks) + i;
//
//			mesh.GetVertex(index) = { p, n, t, uv };
//
//		}
//	}
//
//	uint32_t indicesIndex = 0;
//	// Fill index data
//	for (uint32_t j = 0; j < slices-1; ++j)
//	{
//		for (uint32_t i = 0; i <= stacks; ++i)
//		{
//			const uint32_t a = i % (stacks + 1);
//			const uint32_t b = (i + 1) % (stacks + 1);
//			const uint32_t c = j * (stacks + 1);
//			const uint32_t d = (j + 1) * (stacks + 1);
//
//			//When i==0 && j==0
//			//TRIANGLE 1
//			mesh.GetIndex(indicesIndex) = a + d; //4
//			indicesIndex++;
//			mesh.GetIndex(indicesIndex) = b + c;
//			indicesIndex++;						 //1
//			mesh.GetIndex(indicesIndex) = a + c;
//			indicesIndex++;						 //0
//
//			//When i==0 && j==0
//			//TRIANGLE 2
//			mesh.GetIndex(indicesIndex) = a + d; //4
//			indicesIndex++;
//			mesh.GetIndex(indicesIndex) = b + d;
//			indicesIndex++;						 //5
//			mesh.GetIndex(indicesIndex) = b + c;
//			indicesIndex++;						 //1
//		}
//	}
//}


void MeshBuilder::CreatePlane(Mesh& mesh)
{
	Vertex* kPlane = new Vertex[4];
	Vertex kVertices[] =
	{
		//FACE FRONT-----------------------------------------------------------------------------------------------------------------------------------------
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, //0
		{ {  1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }, //1
		{ {  1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } }, //2
		{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } }  //3

	};

	const int KVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);

	uint32_t* kCubeIndices = new uint32_t[6];
	uint32_t kIndices[] =
	{
		//Front
		0, 1, 2,
		0, 2, 3
	};

	constexpr int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);

	mesh.Allocate(KVertexCount, kIndexCount);

	for (uint32_t i = 0; i < 4; ++i)
	{
		mesh.GetVertex(i) = kVertices[i];
	}

	for (uint32_t i = 0; i < 6; ++i)
	{
		mesh.GetIndex(i) = kIndices[i];
	}
}

void MeshBuilder::CreateCylinder(Mesh& mesh, uint32_t slices, uint32_t stacks)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	float stackHeight = 1.0f / stacks; //Height = 1.0f

	//Amount that we are going to move stack level from bottom to top
	float radiusStep = 0.0f; //Used if top radius and bottom radius are different.

	uint32_t ringCount = stacks + 1;

	float r = 0.5f;

	//vertices of the ring
	float dTheta = Math::kTwoPi / slices;

	Vertex vertex;

	uint32_t lastBottomIndex{ 0 };

	//Computing vertices
	for (uint32_t i{ 0 }; i < ringCount; ++i)
	{
		float y = -0.5f * 1.0f + i * stackHeight;

		for (uint32_t j{ 0 }; j <= slices; ++j)
		{

			float c = cos(j*dTheta);
			float s = sin(j*dTheta);

			vertex.position = { r * c, y, r * s };
			vertex.uv = { static_cast<float>(j) / slices, 1.0f - static_cast<float>(i) / stacks };
			vertex.tangent = { -s, 0.0f, c };

			Math::Vector3 bitangent{ 0.0f, -1.0f, 0.0f };
			vertex.normal = Math::Cross(vertex.tangent, bitangent);

			vertices.push_back(vertex);
		}
		
	}

	uint32_t ringVertexCount = slices + 1;

	for (uint32_t i{ 0 }; i < stacks; ++i)
	{
		for (uint32_t j{ 0 }; j < slices; ++j)
		{
			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);
			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);
			indices.push_back(i * ringVertexCount + j + 1);
		}
	}

	//Build Top Cap
	uint32_t baseIndex = static_cast<uint32_t>(vertices.size());
	float y = 0.5f * 1.0f;//Height = 1.0f

	for (uint32_t i{ 0 }; i <= slices; ++i)
	{
		float x = 0.5f * cos(i * dTheta);
		float z = 0.5f * sin(i * dTheta);

		float u = x / 1.0f + 0.5f;
		float v = z / 1.0f + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, 1.0f, 0.0f };
		vertex.tangent = { 1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertices.push_back(vertex);
	}

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, 1.0f, 0.0f };
	vertex.tangent = { 1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertices.push_back(vertex);

	// Index of center vertex.
	uint32_t centerIndex = static_cast<uint32_t>(vertices.size() - 1);

	for (uint32_t i{ 0 }; i < slices; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}

	//Bottom Cap
	y = -0.5f * 1.0f; //height = 1.0f

	lastBottomIndex = static_cast<uint32_t>(vertices.size());
	for (uint32_t i{ 0 }; i <= slices; ++i)
	{
		float x = 0.5f * sin(i * dTheta);
		float z = 0.5f * cos(i * dTheta);

		float u = x / 1.0f + 0.5f;
		float v = z / 1.0f + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, -1.0f, 0.0f };
		vertex.tangent = { -1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertices.push_back(vertex);
		
	}

	

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, -1.0f, 0.0f };
	vertex.tangent = { -1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertices.push_back(vertex);

	// Index of center vertex.
	//baseIndex = static_cast<uint32_t>(vertices.size());
	centerIndex = static_cast<uint32_t>(vertices.size() - 1);
	
	for (uint32_t i{ 0 }; i < slices; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(lastBottomIndex + i + 1);
		indices.push_back(lastBottomIndex + i);
	}

	mesh.Allocate(static_cast<uint32_t>(vertices.size()), static_cast<uint32_t>(indices.size()));
	for (uint32_t i{ 0 }; i < vertices.size(); ++i)
	{
		mesh.GetVertex(i) = vertices[i];
	}

	for (uint32_t i{ 0 }; i < indices.size(); ++i)
	{
		mesh.GetIndex(i) = indices[i];
	}
}

//Gizmos meshes
void MeshBuilder::CreateCustomCylinder(Mesh& mesh, float bottomRadius, float topRadius, float height, uint32_t slices, uint32_t stacks)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	float stackHeight = height / stacks; 

	//Amount that we are going to move stack level from bottom to top
	float radiusStep = (topRadius - bottomRadius)/stacks; //Used if top radius and bottom radius are different.

	uint32_t ringCount = stacks + 1;

	//vertices of the ring
	float dTheta = Math::kTwoPi / slices;

	Vertex vertex;

	uint32_t lastBottomIndex{ 0 };

	//Computing vertices
	for (uint32_t i{ 0 }; i < ringCount; ++i)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;


		for (uint32_t j{ 0 }; j <= slices; ++j)
		{
			float c = cos(j*dTheta);
			float s = sin(j*dTheta);

			vertex.position = { r * c, y, r * s };
			vertex.uv = { static_cast<float>(j) / slices, 1.0f - static_cast<float>(i) / stacks };
			vertex.tangent = { -s, 0.0f, c };

			float dr = bottomRadius - topRadius;

			Math::Vector3 bitangent{ dr*c, -height, dr*s };
			vertex.normal = Math::Normalize(Math::Cross(vertex.tangent, bitangent));

			vertices.push_back(vertex);
		}

	}

	uint32_t ringVertexCount = slices + 1;

	for (uint32_t i{ 0 }; i < stacks; ++i)
	{
		for (uint32_t j{ 0 }; j < slices; ++j)
		{
			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);

			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);
			indices.push_back(i * ringVertexCount + j + 1);
		}
	}

	//Build Top Cap
	uint32_t baseIndex = static_cast<uint32_t>(vertices.size());
	float y = 0.5f * height;//Height = 1.0f

	for (uint32_t i{ 0 }; i <= slices; ++i)
	{
		float x = topRadius * cos(i * dTheta);
		float z = topRadius * sin(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, 1.0f, 0.0f };
		vertex.tangent = { 1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertices.push_back(vertex);
	}

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, 1.0f, 0.0f };
	vertex.tangent = { 1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertices.push_back(vertex);

	// Index of center vertex.
	uint32_t centerIndex = static_cast<uint32_t>(vertices.size() - 1);

	for (uint32_t i{ 0 }; i < slices; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}

	//Bottom Cap
	y = -0.5f * height;

	lastBottomIndex = static_cast<uint32_t>(vertices.size());
	for (uint32_t i{ 0 }; i <= slices; ++i)
	{
		//I Changed Here
		float x = bottomRadius * cos(i * dTheta);
		float z = bottomRadius * sin(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, -1.0f, 0.0f };
		vertex.tangent = { 1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertices.push_back(vertex);
	}

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, -1.0f, 0.0f };
	vertex.tangent = { 1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertices.push_back(vertex);

	// Index of center vertex.
	//baseIndex = static_cast<uint32_t>(vertices.size());
	centerIndex = static_cast<uint32_t>(vertices.size() - 1);

	for (uint32_t i{ 0 }; i < slices; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(lastBottomIndex + i);
		indices.push_back(lastBottomIndex + i + 1);
	}

	mesh.Allocate(static_cast<uint32_t>(vertices.size()), static_cast<uint32_t>(indices.size()));
	for (uint32_t i{ 0 }; i < vertices.size(); ++i)
	{
		mesh.GetVertex(i) = vertices[i];
	}

	for (uint32_t i{ 0 }; i < indices.size(); ++i)
	{
		mesh.GetIndex(i) = indices[i];
	}

}


void MeshBuilder::CreateSphere(Mesh& mesh, uint32_t slices, uint32_t rings)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	Vertex vertex;

	const float kSliceStep = Math::kTwoPi / rings; //calcula largura de um slice
	const float kRingStep = Math::kPi / (slices - 1); // Calcula a largura de um ring

	// Fill vertex data
	float uStep = 1.0f / rings;
	float vStep = 1.0f / slices;
	uint32_t index = 0;

	for (uint32_t j = 0; j < slices; ++j)
	{
		const float phi = j * kRingStep;

		for (uint32_t i = 0; i <= rings; ++i)
		{
			const float theta = i * kSliceStep;
			const float y = cos(phi);
			const float r = sqrt(1.0f - (y * y));
			const float s = sin(theta);
			const float c = cos(theta);
			const float x = r * c;
			const float z = r * s;
			Math::Vector3 p(x, y, z);
			Math::Vector3 n(x, y, z);
			Math::Vector3 t(-s, 0.0f, c);
			Math::Vector2 uv(i *(1.0f / rings), j*(1.0f / slices));
			vertex = { p, n, t, uv};
			vertices.push_back(vertex);
		}
	}
	// Fill index data
	for (uint32_t j = 0; j < slices - 1; ++j)
	{
		for (uint32_t i = 0; i <= rings; ++i)
		{
			const uint32_t a = i % (rings + 1);
			const uint32_t b = (i + 1) % (rings + 1);
			const uint32_t c = j * (rings + 1);
			const uint32_t d = (j + 1) * (rings + 1);
			indices.push_back(a + c);
			indices.push_back(b + c);
			indices.push_back(a + d);
			indices.push_back(b + c);
			indices.push_back(b + d);
			indices.push_back(a + d);
		}
	}

	mesh.Allocate(static_cast<uint32_t>(vertices.size()), static_cast<uint32_t>(indices.size()));

	for (uint32_t i = 0; i < vertices.size(); ++i)
	{
		mesh.GetVertex(i) = vertices[i];
	}

	for (uint32_t i = 0; i < indices.size(); ++i)
	{
		mesh.GetIndex(i) = indices[i];
	}
}

void MeshBuilder::CreateSkySphere(Mesh& mesh, uint32_t rings, uint32_t slices)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	Vertex vertex;

	const float kSliceStep = Math::kTwoPi / rings; //calcula largura de um slice
	const float kRingStep = Math::kPi / (slices - 1); // Calcula a largura de um ring

	// Fill vertex data
	float uStep = 1.0f / rings;
	float vStep = 1.0f / slices;
	uint32_t index = 0;

	for (uint32_t j = 0; j < slices; ++j)
	{
		const float phi = j * kRingStep;

		for (uint32_t i = 0; i <= rings; ++i)
		{
			const float theta = i * kSliceStep;
			const float y = cos(phi);
			const float r = sqrt(1.0f - (y * y));
			const float s = sin(theta);
			const float c = cos(theta);
			const float x = r * c;
			const float z = r * s;
			Math::Vector3 p(x, y, z);
			Math::Vector3 n(x, y, z);
			Math::Vector3 t(-s, 0.0f, c);
			Math::Vector2 uv(i *(1.0f / rings), j*(1.0f / slices));
			vertex = { p, n, t, uv };
			vertices.push_back(vertex);
		}
	}
	// Fill index data
	for (uint32_t j = 0; j < slices - 1; ++j)
	{
		for (uint32_t i = 0; i <= rings; ++i)
		{
			const uint32_t a = i % (rings + 1);
			const uint32_t b = (i + 1) % (rings + 1);
			const uint32_t c = j * (rings + 1);
			const uint32_t d = (j + 1) * (rings + 1);
			indices.push_back(a + d);
			indices.push_back(b + c);
			indices.push_back(a + c);

			indices.push_back(a + d);
			indices.push_back(b + d);
			indices.push_back(b + c);
		}
	}

	mesh.Allocate(static_cast<uint32_t>(vertices.size()), static_cast<uint32_t>(indices.size()));

	for (uint32_t i = 0; i < vertices.size(); ++i)
	{
		mesh.GetVertex(i) = vertices[i];
	}

	for (uint32_t i = 0; i < indices.size(); ++i)
	{
		mesh.GetIndex(i) = indices[i];
	}
}