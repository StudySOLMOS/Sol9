#pragma once

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

	MeshBuffer* getMeshBuffer(u32 nIndex);
	u32 getMeshBufferCount() const;
};