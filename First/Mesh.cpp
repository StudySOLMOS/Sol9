#include "PCH.h"
#include "Mesh.h"

Mesh::Mesh()
	: m_MeshBuffers()
{
}

Mesh::~Mesh()
{
	auto remove = [](MeshBuffer* buffer)
	{
		if (buffer)
			delete buffer;
	};

	std::for_each(m_MeshBuffers.begin(), m_MeshBuffers.end(), remove);
}

void Mesh::render(IDirect3DDevice9* pDevice)
{
	auto rendering = [=](MeshBuffer* buffer)
	{
		buffer->render(pDevice);
	};

	std::for_each(m_MeshBuffers.begin(), m_MeshBuffers.end(), rendering);
}

void Mesh::addMeshBuffer(MeshBuffer* pBuffer)
{
	if (!pBuffer)
		return;

	m_MeshBuffers.push_back(pBuffer);
}

MeshBuffer* Mesh::getMeshBuffer(u32 nIndex)
{
	return m_MeshBuffers[nIndex];
}

u32 Mesh::getMeshBufferCount() const
{
	return m_MeshBuffers.size();
}