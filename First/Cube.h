#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
private:
	IDirect3DDevice9* m_pDevice;
	IDirect3DVertexBuffer9* m_pVertex;
	IDirect3DIndexBuffer9* m_pIndex;
	IDirect3DTexture9* m_pTexture;

	D3DXMATRIX m_matLocal;

public:
	Cube(IDirect3DDevice9* pDevice, float fSize, const std::string& strFile);
	virtual ~Cube();

	void update(unsigned int timeMs);
	void render();

private:
	void _setupMesh(float fSize);
	void _loadTexture(const std::string& strFile);
};