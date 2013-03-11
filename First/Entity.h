#pragma once

class Mesh;
class Texture;

class Entity
{
private:
	Mesh* m_pOwnerMesh;
	D3DXMATRIX m_matLocal;

public:
	Entity(Mesh* pMesh);
	virtual ~Entity();

	void update(unsigned int timeMs);
	void render(IDirect3DDevice9* pDevice);

	void setTexture(u32 nLayer, Texture* pTexture);
};