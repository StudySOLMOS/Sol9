#pragma once

class Cube
{
private:
	struct TEXCOORD
	{
		float u, v;

		TEXCOORD() : u(0.0f), v(0.0f) {}
		TEXCOORD(float _u, float _v) : u(_u), v(_v) {}
	};

	struct VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		TEXCOORD texcoord;

		VERTEX() : position(), normal(), texcoord() {}
		VERTEX(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
			: position(_x, _y, _z), normal(_nx, _ny, _nz), texcoord(_u, _v) {}

		enum {FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)};
	};

	typedef std::vector<VERTEX> _Vertices;

	struct INDEX
	{
		DWORD a, b, c;

		INDEX() : a(0), b(0), c(0) {}
		INDEX(DWORD _a, DWORD _b, DWORD _c) : a(_a), b(_b), c(_c) {}
	};

	typedef std::vector<INDEX> _Indices;

	IDirect3DDevice9* m_pDevice;
	IDirect3DVertexBuffer9* m_pVertex;
	IDirect3DIndexBuffer9* m_pIndex;
	IDirect3DTexture9* m_pTexture;

	////// shader
	IDirect3DVertexShader9* m_pVertexShader;
	IDirect3DPixelShader9* m_pPixelShader;
	ID3DXConstantTable* m_pVSConstantsTable;
	ID3DXConstantTable* m_pPSConstantsTable;
	////// shader

	D3DXMATRIX m_matWorld;

public:
	Cube(IDirect3DDevice9* pDevice, float fSize, const std::wstring& strFile);
	virtual ~Cube();

	void update(unsigned int timeMs);
	void render();

private:
	void _setupMesh(float fSize);
	void _loadTexture(const std::wstring& strFile);

	bool _initVertexShader();
	bool _initPixelShader();
};