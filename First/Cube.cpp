#include "stdafx.h"
#include "Cube.h"

//#define _SHADER_ON_

Cube::Cube(IDirect3DDevice9* pDevice)
	: m_pDevice(pDevice), m_pVertex(nullptr), m_pIndex(nullptr), m_pTexture(nullptr)
	, m_matWorld()
	////// shader
	, m_pVertexShader(nullptr), m_pPixelShader(nullptr)
	, m_pVSConstantsTable(nullptr), m_pPSConstantsTable(nullptr)
	////// shader
{
	D3DXMatrixIdentity(&m_matWorld);
#if defined (_SHADER_ON_)
	_initVertexShader();
	_initPixelShader();
#endif
}

Cube::~Cube()
{
	if (m_pVertex)
		m_pVertex->Release();

	if (m_pIndex)
		m_pIndex->Release();

	if (m_pTexture)
		m_pTexture->Release();

	////// shader
	if (m_pVSConstantsTable)
		m_pVSConstantsTable->Release();

	if (m_pPSConstantsTable)
		m_pPSConstantsTable->Release();

	if (m_pVertexShader)
		m_pVertexShader->Release();

	if (m_pPixelShader)
		m_pPixelShader->Release();
	////// shader
}

void Cube::load(const std::wstring& stdFile)
{
}

void Cube::update(unsigned int timeMs)
{
	D3DXVECTOR3 vRotate(0.0f, 0.1f, 0.0f);
	vRotate *= (float)timeMs / 1000.0f;

	D3DXMATRIX matTemp;
	D3DXMatrixRotationYawPitchRoll(&matTemp, vRotate.y, vRotate.x, vRotate.z);
	m_matWorld = matTemp * m_matWorld;
}

void Cube::render()
{
	if (!m_pDevice)
		return;

	if (!m_pVertex || !m_pIndex)
		return;

#if defined (_SHADER_ON_)
	////// shader
	D3DXMATRIX v, p;
	m_pDevice->GetTransform(D3DTS_VIEW, &v);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &p);

	m_pVSConstantsTable->SetMatrix(m_pDevice, "matWorld", &m_matWorld);
	m_pVSConstantsTable->SetMatrix(m_pDevice, "matView", &v);
	m_pVSConstantsTable->SetMatrix(m_pDevice, "matProj", &p);

	m_pDevice->SetVertexShader(m_pVertexShader);
	m_pDevice->SetPixelShader(m_pPixelShader);
	////// shader
#else if
	m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
#endif

	if (m_pTexture)
	{
		m_pDevice->SetTexture(0, m_pTexture);
		m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	}

	m_pDevice->SetStreamSource(0, m_pVertex, 0, sizeof(VERTEX));
	m_pDevice->SetFVF(VERTEX::FVF);
	m_pDevice->SetIndices(m_pIndex);
	//m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVertices, 0, m_nTile * m_nTile * 2);
}

//void Cube::_createHeightMap(_Vertices& Vertices)
//{
//	_setupVertices(Vertices);
//	_buildVertices(Vertices);
//}
//
//void Cube::_loadHeightMapFromImage(const std::wstring& stdFile, _Vertices& Vertices, int nSmooth)
//{
//	if (!m_pDevice)
//		return;
//
//	IDirect3DTexture9* pTex;
//	D3DXCreateTextureFromFileEx(m_pDevice, stdFile.c_str(),
//		D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
//		D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &pTex);
//
//	if (!pTex)
//		return;
//
//	D3DSURFACE_DESC ddsd;
//	pTex->GetLevelDesc(0, &ddsd);
//	m_nTile = ddsd.Width - 1;
//	D3DFORMAT format = ddsd.Format;
//	m_nVertices = (m_nTile + 1) * (m_nTile + 1);
//
//	// create
//	_setupVertices(Vertices);
//
//	D3DLOCKED_RECT tex;
//	pTex->LockRect(0, &tex, nullptr, D3DLOCK_READONLY);
//
//	for (int z = 0; z <= m_nTile; ++z)
//	{
//		for (int x = 0; x <= m_nTile; ++x)
//		{
//			VERTEX& v = Vertices[z * (m_nTile + 1) + x];
//
//			float y = 0.0f;
//
//			if (format == D3DFMT_X8R8G8B8 || format == D3DFMT_X8B8G8R8 ||
//				format == D3DFMT_A8R8G8B8 || format == D3DFMT_A8B8G8R8)
//			{
//				DWORD c = (*((DWORD*)tex.pBits + x + z * tex.Pitch / sizeof(DWORD)));
//				float r = (float)(c >> 16 & 0xff);
//				float g = (float)(c >> 8 & 0xff);
//				float b = (float)(c & 0xff);
//				y = 0.2f * (std::max(std::max(r, g), b) + std::min(std::min(r, g), b));
//				//y = (r + g + b) / 3.0f * 0.3f;
//			}
//			else if (format == D3DFMT_L8)
//			{
//				y = (float)(*((BYTE*)tex.pBits + x + z * tex.Pitch) >> 2);
//			}
//
//			if (y < 10.0f)
//				v.color = D3DCOLOR_XRGB(255, 249, 157);
//			else if (y < 20.0f)
//				v.color = D3DCOLOR_XRGB(124, 197, 118);
//			else if (y < 30.0f)
//				v.color = D3DCOLOR_XRGB(  0, 166,  81);
//			else if (y < 40.0f)
//				v.color = D3DCOLOR_XRGB( 25, 123,  48);
//			else if (y < 50.0f)
//				v.color = D3DCOLOR_XRGB(115, 100,  87);
//			else if (y < 60.0f)
//				v.color = D3DCOLOR_XRGB(180, 150,  170);
//			else
//				v.color = D3DCOLOR_XRGB(255, 255, 255);
//
//			v.position.y = y * m_fScale;
//		}
//	}
//
//	pTex->UnlockRect(0);
//	pTex->Release();
//
//	_smoothMap(Vertices, nSmooth);
//	_calculateNormals(Vertices);
//
//	_buildVertices(Vertices);
//}
//
//void Cube::_setupVertices(_Vertices& Vertices)
//{
//	if (!m_pDevice)
//		return;
//
//	float halfsize = (float)m_nTile / 2.0f;
//	Vertices.resize(m_nVertices);
//
//	for (int z = 0; z <= m_nTile; ++z)
//	{
//		for (int x = 0; x <= m_nTile; ++x)
//		{
//			VERTEX& v = Vertices[z * (m_nTile + 1) + x];
//			v.position = D3DXVECTOR3((float)x - halfsize, 0.0f, (float)z - halfsize);
//			v.position *= m_fScale;
//			v.normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			v.color = 0xffffffff;
//			v.texcoord.u = ((float)x / (float)m_nTile) * m_fDetail;
//			v.texcoord.v = (1.0f - (float)z / (float)m_nTile) * m_fDetail;
//		}
//	}
//
//	int i = 0;
//	_Indices index(m_nTile * m_nTile * 2);
//
//	for (int z = 0; z < m_nTile; ++z)
//	{
//		for (int x = 0; x < m_nTile; ++x)
//		{
//			index[i].a = (m_nTile + 1) * (z + 0) + x + 0;
//			index[i].b = (m_nTile + 1) * (z + 1) + x + 0;
//			index[i].c = (m_nTile + 1) * (z + 0) + x + 1;
//			++i;
//
//			index[i].a = (m_nTile + 1) * (z + 1) + x + 0;
//			index[i].b = (m_nTile + 1) * (z + 1) + x + 1;
//			index[i].c = (m_nTile + 1) * (z + 0) + x + 1;
//			++i;
//		}
//	}
//
//	m_pDevice->CreateIndexBuffer(sizeof(INDEX) * index.size(), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndex, nullptr);
//
//	int size = sizeof(INDEX) * index.size();
//	void* indices;
//	m_pIndex->Lock(0, sizeof(INDEX) * index.size(), &indices, 0);
//	//memcpy(indices, index.data(), size);
//	memmove_s(indices, size, index.data(), size);
//	m_pIndex->Unlock();
//}
//
//void Cube::_buildVertices(_Vertices& Vertices)
//{
//	if (!m_pDevice)
//		return;
//
//	m_pDevice->CreateVertexBuffer((sizeof(VERTEX) * Vertices.size()), 0, VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertex, nullptr);
//	
//	int size = sizeof(VERTEX) * Vertices.size();
//	void* vertices;
//	m_pVertex->Lock(0, sizeof(VERTEX) * Vertices.size(), &vertices, 0);
//	//memcpy(vertices, Vertices.data(), size);
//	memmove_s(vertices, size, Vertices.data(), size);
//	m_pVertex->Unlock();
//}
//
//void Cube::_calculateNormals(std::vector<VERTEX>& Vertices)
//{
//	D3DXVECTOR3 a, b, c, t;
//
//	for (int z = 1; z < m_nTile; ++z)
//	{
//		for (int x = 1; x < m_nTile; ++x)
//		{
//			int Z = m_nTile + 1;
//			int X = 1;
//			int C = Z * z + x;
//
//			D3DXVECTOR3 n(0.0f, 0.0f, 0.0f);
//
//			// mapping for calculate.
//			int vertexmap[8][3] =
//			{
//				{C-X-Z,	C-X,	C},
//				{C-X-Z,	C-Z,	C},
//				{C-X,	C-X+Z,	C+Z},
//				{C-X,	C+Z,	C},
//
//				{C+Z,	C,		C+X+Z},
//				{C+Z,	C+X+Z,	C+X},
//				{C-Z,	C,		C+X+Z},
//				{C-Z,	C+X,	C+X-Z}
//			};
//
//			for (int i = 0; i < 8; ++i)
//			{
//				a = Vertices[vertexmap[i][0]].position;
//				b = Vertices[vertexmap[i][1]].position;
//				c = Vertices[vertexmap[i][2]].position;
//
//				b -= a;
//				c -= a;
//				D3DXVec3Cross(&t, &b, &c);
//				D3DXVec3Normalize(&t, &t);
//
//				n += t;
//			}
//
//			if (D3DXVec3LengthSq(&n) != 0.0f)
//				D3DXVec3Normalize(&n, &n);
//			else
//				n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//			Vertices[C].normal = n;
//		}
//	}
//}
//
//void Cube::_smoothMap(std::vector<VERTEX>& Vertices, int nFactor)
//{
//	for (int f = 0; f < nFactor; ++f)
//	{
//		for (int z = 1; z < m_nTile; ++z)
//		{
//			for (int x = 1; x < m_nTile; ++x)
//			{
//				int Z = m_nTile + 1;
//				int X = 1;
//				int C = Z * z + x;
//
//				int vertexmap[4] = {C-X, C+X, C-Z, C+Z};
//
//				float smooth = 0.0f;
//
//				for (int i = 0; i < 4; ++i)
//					smooth += Vertices[vertexmap[i]].position.y;
//
//				Vertices[C].position.y = smooth * 0.25f;
//			}
//		}
//	}
//}

bool Cube::_initVertexShader()
{
	ID3DXBuffer* buffer = nullptr;
	ID3DXBuffer* error = nullptr;

	HRESULT r = 0;
	r = D3DXCompileShaderFromFile(L"vs.hlsl", nullptr, nullptr,
		"vs_main", "vs_2_0", 0, &buffer, &error, &m_pVSConstantsTable);

	if (FAILED(r))
	{
		if (error)
		{
			char* e = (char*)error->GetBufferPointer();
			error->Release();

			if (buffer)
				buffer->Release();
		}

		return false;
	}

	if (error)
		error->Release();

	if (buffer)
	{
		r = m_pDevice->CreateVertexShader((DWORD*)buffer->GetBufferPointer(), &m_pVertexShader);

		if (FAILED(r))
		{
			buffer->Release();
			return false;
		}

		buffer->Release();
		return true;
	}

	return false;
}

bool Cube::_initPixelShader()
{
	ID3DXBuffer* buffer = nullptr;
	ID3DXBuffer* error = nullptr;

	HRESULT r = 0;
	r = D3DXCompileShaderFromFile(L"ps.hlsl", nullptr, nullptr,
		"ps_main", "ps_2_0", 0, &buffer, &error, &m_pPSConstantsTable);

	if (FAILED(r))
	{
		if (error)
		{
			char* e = (char*)error->GetBufferPointer();
			error->Release();

			if (buffer)
				buffer->Release();
		}

		return false;
	}

	if (error)
		error->Release();

	if (buffer)
	{
		r = m_pDevice->CreatePixelShader((DWORD*)buffer->GetBufferPointer(), &m_pPixelShader);

		if (FAILED(r))
		{
			buffer->Release();
			return false;
		}

		buffer->Release();
		return true;
	}

	return false;
}