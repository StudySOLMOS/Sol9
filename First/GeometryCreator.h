#pragma once

class Mesh;

class GeometryCreator
{
private:
	IDirect3DDevice9* m_pDevice;

public:
	GeometryCreator(IDirect3DDevice9* pDevice);

	Mesh* createCube(f32 fSize = 10.0f);
};