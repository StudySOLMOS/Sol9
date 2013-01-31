#pragma once

class Cube
{
private:
	struct TEXCOORD
	{
		float u, v;

		TEXCOORD() : u(0.0f), v(0.0f) {}
	};

	struct VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DCOLOR color;
		TEXCOORD texcoord;

		VERTEX() : position(), normal(), color(0), texcoord() {}

		enum {FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)};
	};

	typedef std::vector<VERTEX> _Vertices;

	struct INDEX
	{
		DWORD a, b, c;

		INDEX() : a(0), b(0), c(0) {}
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
	Cube(IDirect3DDevice9* pDevice);
	~Cube();

	void load(const std::wstring& stdFile);
	void update(unsigned int timeMs);
	void render();

private:
	bool _initVertexShader();
	bool _initPixelShader();
};