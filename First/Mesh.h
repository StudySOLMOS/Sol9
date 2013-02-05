#pragma once

class Mesh
{
protected:
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

		enum
		{
			FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
		};
	};

	struct INDEX
	{
		DWORD a, b, c;

		INDEX() : a(0), b(0), c(0) {}
		INDEX(DWORD _a, DWORD _b, DWORD _c) : a(_a), b(_b), c(_c) {}
	};

	typedef std::vector<VERTEX> _Vertices;
	typedef std::vector<INDEX> _Indices;

public:
	Mesh();
	virtual ~Mesh();
};