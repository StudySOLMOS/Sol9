#include "PCH.h"
#include "GeometryCreator.h"
#include "Mesh.h"

GeometryCreator::GeometryCreator(IDirect3DDevice9* pDevice)
	: m_pDevice(pDevice)
{
}

Mesh* GeometryCreator::createCube(f32 fSize)
{
	if (!m_pDevice)
		return nullptr;

	MeshBuffer* cube = new MeshBuffer;

	_Vertices v;
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 1, 0, 0, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 1, 0, 0, 1));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 1, 0, 1, 1));
	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 1, 0, 1, 0));

	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 0, 1, 0, 0));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 0, 1, 0, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, 0, 1, 1, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, 0, 1, 1, 0));

	v.push_back(VERTEX(-fSize, fSize, -fSize, -1, 0, 0, 0, 0));
	v.push_back(VERTEX(-fSize, fSize, fSize, -1, 0, 0, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, -1, 0, 0, 1, 1));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, -1, 0, 0, 1, 0));

	v.push_back(VERTEX(fSize, fSize, fSize, 1, 0, 0, 0, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 1, 0, 0, 0, 1));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 1, 0, 0, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 1, 0, 0, 1, 0));

	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 0, -1, 0, 0));
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 0, -1, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, 0, -1, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, 0, -1, 1, 0));

	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, -1, 0, 0, 0));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, -1, 0, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, -1, 0, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, -1, 0, 1, 0));

	m_pDevice->CreateVertexBuffer(sizeof(VERTEX) * v.size(), 0, VERTEX::FVF, D3DPOOL_MANAGED, &cube->m_pVertex, nullptr);
	
	int size = sizeof(VERTEX) * v.size();
	void* vertices;
	cube->m_pVertex->Lock(0, sizeof(VERTEX) * v.size(), &vertices, 0);
	memmove_s(vertices, size, v.data(), size);
	cube->m_pVertex->Unlock();


	_Indices i;
	i.push_back(INDEX(0, 3, 1));
	i.push_back(INDEX(1, 3, 2));
	
	i.push_back(INDEX(4, 7, 5));
	i.push_back(INDEX(5, 7, 6));

	i.push_back(INDEX(8, 11, 9));
	i.push_back(INDEX(9, 11, 10));

	i.push_back(INDEX(12, 15, 13));
	i.push_back(INDEX(13, 15, 14));

	i.push_back(INDEX(16, 19, 17));
	i.push_back(INDEX(17, 19, 18));

	i.push_back(INDEX(20, 23, 21));
	i.push_back(INDEX(21, 23, 22));

	m_pDevice->CreateIndexBuffer(sizeof(INDEX) * i.size(), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &cube->m_pIndex, nullptr);

	size = sizeof(INDEX) * i.size();
	void* indices;
	cube->m_pIndex->Lock(0, sizeof(INDEX) * i.size(), &indices, 0);
	memmove_s(indices, size, i.data(), size);
	cube->m_pIndex->Unlock();


	cube->m_nVertices = v.size();
	cube->m_nIndices = i.size();

	Mesh* mesh = new Mesh;
	mesh->addMeshBuffer(cube);
	return mesh;
}