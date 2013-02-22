#pragma once

class Mesh;

class Renderer
{
private:
	IDirect3DDevice9* m_pDevice;

public:
	Renderer(IDirect3DDevice9* pDevice);
	~Renderer();
};