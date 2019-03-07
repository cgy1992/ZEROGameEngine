#include "Precompiled.h"
#include "GraphicsUtil.h"

using namespace ZERO;
using namespace ZERO::Graphics;

void GraphicsUtil::ComputeNormals(Mesh& mesh)
{
	uint32_t numberOfIndices = mesh.GetIndicesCount();

	uint32_t vertexCount = mesh.GetVertexCount();

	std::unique_ptr<Math::Vector3[]> normals = std::make_unique<Math::Vector3[]>(vertexCount);

	uint32_t currentIndex;
	uint32_t frontIndex;
	uint32_t rightIndex;

	uint32_t meshIndexCurrent;
	uint32_t meshIndexFront;
	uint32_t meshIndexRight;

	Math::Vector3 front = { 0.0f, 0.0f, 0.0f };
	Math::Vector3 right = { 0.0f, 0.0f, 0.0f };

	Math::Vector3 normal = { 0.0f, 0.0f, 0.0f };

	for (uint32_t i = 0; i < numberOfIndices; i += 3)
	{
		currentIndex = i;
		frontIndex = i + 1;
		rightIndex = i + 2;

		meshIndexCurrent = mesh.GetIndex(currentIndex);
		meshIndexFront = mesh.GetIndex(frontIndex);
		meshIndexRight = mesh.GetIndex(rightIndex);

		front = mesh.GetVertex(meshIndexFront).position - mesh.GetVertex(meshIndexCurrent).position;
		right = mesh.GetVertex(meshIndexRight).position - mesh.GetVertex(meshIndexCurrent).position;

		normal = Math::Normalize(Math::Cross(front, right));

		normals[meshIndexCurrent] += normal;
		normals[meshIndexFront] += normal;
		normals[meshIndexRight] += normal;
	}

	for (uint32_t i = 0; i < vertexCount; i++)
	{
		normals[i] = Math::Normalize(normals[i]);
		mesh.GetVertex(i).normal = normals[i];
	}
}

void GraphicsUtil::ComputeNormals(SkinMesh& mesh)
{
	uint32_t numberOfIndices = mesh.GetIndicesCount();

	uint32_t vertexCount = mesh.GetVertexCount();

	std::unique_ptr<Math::Vector3[]> normals = std::make_unique<Math::Vector3[]>(vertexCount);

	uint32_t currentIndex;
	uint32_t frontIndex;
	uint32_t rightIndex;

	uint32_t meshIndexCurrent;
	uint32_t meshIndexFront;
	uint32_t meshIndexRight;

	Math::Vector3 front = { 0.0f, 0.0f, 0.0f };
	Math::Vector3 right = { 0.0f, 0.0f, 0.0f };

	Math::Vector3 normal = { 0.0f, 0.0f, 0.0f };

	for (uint32_t i = 0; i < numberOfIndices; i += 3)
	{
		currentIndex = i;
		frontIndex = i + 1;
		rightIndex = i + 2;

		meshIndexCurrent = mesh.GetIndex(currentIndex);
		meshIndexFront = mesh.GetIndex(frontIndex);
		meshIndexRight = mesh.GetIndex(rightIndex);

		front = mesh.GetVertex(meshIndexFront).position - mesh.GetVertex(meshIndexCurrent).position;
		right = mesh.GetVertex(meshIndexRight).position - mesh.GetVertex(meshIndexCurrent).position;

		normal = Math::Normalize(Math::Cross(front, right));

		normals[meshIndexCurrent] += normal;
		normals[meshIndexFront] += normal;
		normals[meshIndexRight] += normal;
	}

	for (uint32_t i = 0; i < vertexCount; i++)
	{
		normals[i] = Math::Normalize(normals[i]);
		mesh.GetVertex(i).normal = normals[i];
	}
}