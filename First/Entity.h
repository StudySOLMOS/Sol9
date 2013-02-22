#pragma once

class Mesh;

class Entity
{
private:
	Mesh* m_pOwnerMesh;
	IDirect3DTexture9* m_pTexture;
	D3DXMATRIX m_matLocal;

public:
	Entity(Mesh* pMesh);
	virtual ~Entity();

	void update(unsigned int timeMs);
	void render(IDirect3DDevice9* pDevice);

	void setTexture(IDirect3DTexture9* pTexture);
};