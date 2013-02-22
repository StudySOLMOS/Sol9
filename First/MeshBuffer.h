#pragma once

struct TEXCOORD
{
	f32 u, v;

	TEXCOORD() : u(0.0f), v(0.0f) {}
	TEXCOORD(f32 _u, f32 _v) : u(_u), v(_v) {}
};

struct VERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	TEXCOORD texcoord;

	VERTEX() : position(), normal(), texcoord() {}
	VERTEX(f32 _x, f32 _y, f32 _z, f32 _nx, f32 _ny, f32 _nz, f32 _u, f32 _v)
		: position(_x, _y, _z), normal(_nx, _ny, _nz), texcoord(_u, _v) {}

	enum
	{
		FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
	};
};

struct INDEX
{
	u32 a, b, c;

	INDEX() : a(0), b(0), c(0) {}
	INDEX(u32 _a, u32 _b, u32 _c) : a(_a), b(_b), c(_c) {}
};

typedef std::vector<VERTEX> _Vertices;
typedef std::vector<INDEX> _Indices;

class GeometryCreator;
class Renderer;

class MeshBuffer
{
private:
	IDirect3DVertexBuffer9* m_pVertex;
	IDirect3DIndexBuffer9* m_pIndex;
	IDirect3DTexture9* m_pTexture;

	u32 m_nVertices;
	u32 m_nIndices;

	friend class GeometryCreator;
	friend class Renderer;

public:
	MeshBuffer();
	~MeshBuffer();

	void render(IDirect3DDevice9* pDevice);
};