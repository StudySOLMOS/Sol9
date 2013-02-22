#pragma once

#include "MeshBuffer.h"

class MeshBuffer;

class Mesh
{
private:
	std::vector<MeshBuffer*> m_MeshBuffers;

public:
	Mesh();
	virtual ~Mesh();

	void render(IDirect3DDevice9* pDevice);

	void addMeshBuffer(MeshBuffer* pBuffer);

	u32 getMeshBufferCount() const;
};