#include "Precompiled.h"
#include "SkinMeshBuilder.h"

using namespace ZERO;
using namespace ZERO::Graphics;

void SkinMeshBuilder::CreateCylinder(SkinMesh& mesh, uint32_t slices, uint32_t stacks, float height, float radius)
{
	std::vector<BoneVertex> vertices;
	std::vector<uint32_t> indices;

	float stackHeight = height / stacks; //Height = 1.0f

	//Amount that we are going to move stack level from bottom to top
	float radiusStep = 0.0f; //Used if top radius and bottom radius are different.

	uint32_t ringCount = stacks + 1;

	float r = radius;

	//vertices of the ring
	float dTheta = Math::kTwoPi / slices;

	BoneVertex vertex;

	//3 Bones
	vertex.boneIndex[0] = 0;
	vertex.boneIndex[1] = 1;
	vertex.boneIndex[2] = 2;
	vertex.boneIndex[3] = 3;

	uint32_t lastBottomIndex{ 0 };

	uint32_t numberOfBones = 4;
	float bonesJointsPositions[4] = { -height/2.0f, -height/4.0f , 0.0f, height / 4.0f};


	//Computing vertices
	for (uint32_t i{ 0 }; i < ringCount; ++i)
	{
		float y = -0.5f * height + i * stackHeight;

		for (uint32_t j{ 0 }; j <= slices; ++j)
		{

			float c = cos(j*dTheta);
			float s = sin(j*dTheta);

			vertex.position = { r * c, y, r * s };
			vertex.uv = { static_cast<float>(j) / slices, 1.0f - static_cast<float>(i) / stacks };
			vertex.tangent = { -s, 0.0f, c };

			Math::Vector3 bitangent{ 0.0f, -1.0f, 0.0f };
			vertex.normal = Math::Cross(vertex.tangent, bitangent);
			

			if (y >= bonesJointsPositions[0] && y <= bonesJointsPositions[1])
			{
				float h = bonesJointsPositions[1] - bonesJointsPositions[0];
				float pos = y - bonesJointsPositions[0];
				vertex.boneWeight[0] = (h - pos) / h;
				vertex.boneWeight[1] = pos / h;
				vertex.boneWeight[2] = 0.0f;
				vertex.boneWeight[3] = 0.0f;
			}
			else if (y >= bonesJointsPositions[1] && y <= bonesJointsPositions[2])
			{
				float h = bonesJointsPositions[2] - bonesJointsPositions[1];
				float pos = y - bonesJointsPositions[1];
				vertex.boneWeight[0] = 0.0f;
				vertex.boneWeight[1] = (h - pos) / h;
				vertex.boneWeight[2] = pos / h;
				vertex.boneWeight[3] = 0.0f;
			}
			else if (y >= bonesJointsPositions[2] && y <= bonesJointsPositions[3])
			{
				float h = bonesJointsPositions[3] - bonesJointsPositions[2];
				float pos = y - bonesJointsPositions[2];
				vertex.boneWeight[0] = 0.0f;
				vertex.boneWeight[1] = 0.0f;
				vertex.boneWeight[2] = (h - pos) / h;
				vertex.boneWeight[3] =  pos / h;
			}
			else if (y >= bonesJointsPositions[3] && y <= height)
			{
				vertex.boneWeight[0] = 0.0f;
				vertex.boneWeight[1] = 0.0f;
				vertex.boneWeight[2] = 0.0f;
				vertex.boneWeight[3] = 1.0f;
			}
			

			//Still have to figure this part out.
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
		float x = r * cos(i * dTheta);
		float z = r * sin(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, 1.0f, 0.0f };
		vertex.tangent = { 1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertex.boneWeight[0] = 0.0f;
		vertex.boneWeight[1] = 0.0f;
		vertex.boneWeight[2] = 0.0f;
		vertex.boneWeight[3] = 1.0f;

		vertices.push_back(vertex);
	}

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, 1.0f, 0.0f };
	vertex.tangent = { 1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertex.boneWeight[0] = 0.0f;
	vertex.boneWeight[1] = 0.0f;
	vertex.boneWeight[2] = 0.0f;
	vertex.boneWeight[3] = 1.0f;

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
	y = -0.5f * height; //height = 1.0f

	lastBottomIndex = static_cast<uint32_t>(vertices.size());
	for (uint32_t i{ 0 }; i <= slices; ++i)
	{
		float x = r * sin(i * dTheta);
		float z = r * cos(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertex.position = { x, y, z };
		vertex.normal = { 0.0f, -1.0f, 0.0f };
		vertex.tangent = { -1.0f, 0.0f, 0.0f };
		vertex.uv = { u, v };

		vertex.boneWeight[0] = 0.0f;
		vertex.boneWeight[1] = 0.0f;
		vertex.boneWeight[2] = 0.0f;
		vertex.boneWeight[3] = 0.0f;

		vertices.push_back(vertex);

	}

	//Cap center vertex
	vertex.position = { 0.0f, y, 0.0f };
	vertex.normal = { 0.0f, -1.0f, 0.0f };
	vertex.tangent = { -1.0f, 0.0f, 0.0f };
	vertex.uv = { 0.5f, 0.5f };

	vertex.boneWeight[0] = 0.0f;
	vertex.boneWeight[1] = 0.0f;
	vertex.boneWeight[2] = 0.0f;
	vertex.boneWeight[3] = 0.0f;

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

void SkinMeshBuilder::CreatePlane(SkinMesh& mesh)
{
	BoneVertex* kPlane = new BoneVertex[4];
	BoneVertex kVertices[] =
	{
		//FACE FRONT-----------------------------------------------------------------------------------------------------------------------------------------
	{ { -1.0f,  1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } }, //0
	{ {  1.0f,  1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f } }, //1
	{ {  1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 1.0f } }, //2
	{ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 1.0f } }  //3

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