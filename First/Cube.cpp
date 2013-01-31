#include "stdafx.h"
#include "Cube.h"

//#define _SHADER_ON_

Cube::Cube(IDirect3DDevice9* pDevice, float fSize)
	: m_pDevice(pDevice)
	, m_pVertex(nullptr), m_pIndex(nullptr), m_pTexture(nullptr)
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

	_setupMesh(fSize);
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
	D3DXVECTOR3 vRotate(2.0f, 1.5f, 1.0f);
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
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

void Cube::_setupMesh(float fSize)
{
	if (!m_pDevice)
		return;

	_Vertices v;
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 1, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 1, 0));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 1, 0));
	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 1, 0));

	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 0, 1));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 0, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, 0, 1));

	v.push_back(VERTEX(-fSize, fSize, -fSize, -1, 0, 0));
	v.push_back(VERTEX(-fSize, fSize, fSize, -1, 0, 0));
	v.push_back(VERTEX(-fSize, -fSize, fSize, -1, 0, 0));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, -1, 0, 0));

	v.push_back(VERTEX(fSize, fSize, fSize, 1, 0, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 1, 0, 0));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 1, 0, 0));
	v.push_back(VERTEX(fSize, -fSize, fSize, 1, 0, 0));

	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 0, -1));
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 0, -1));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, 0, -1));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, 0, -1));

	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, -1, 0));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, -1, 0));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, -1, 0));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, -1, 0));

	m_pDevice->CreateVertexBuffer((sizeof(VERTEX) * v.size()), 0, VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertex, nullptr);
	
	int size = sizeof(VERTEX) * v.size();
	void* vertices;
	m_pVertex->Lock(0, sizeof(VERTEX) * v.size(), &vertices, 0);
	memmove_s(vertices, size, v.data(), size);
	m_pVertex->Unlock();


	_Indices i;
	i.push_back(INDEX(0, 3, 1));
	i.push_back(INDEX(1, 3, 2));
	
	i.push_back(INDEX(4, 7, 5));
	i.push_back(INDEX(5, 7, 6));

	i.push_back(INDEX(8, 11, 9));
	i.push_back(INDEX(9, 11, 10));

	i.push_back(INDEX(12, 15, 13));
	i.push_back(INDEX(13, 15, 14));

	i.push_back(INDEX(16, 19, 17));
	i.push_back(INDEX(17, 19, 18));

	i.push_back(INDEX(20, 23, 21));
	i.push_back(INDEX(21, 23, 22));

	m_pDevice->CreateIndexBuffer(sizeof(INDEX) * i.size(), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndex, nullptr);

	size = sizeof(INDEX) * i.size();
	void* indices;
	m_pIndex->Lock(0, sizeof(INDEX) * i.size(), &indices, 0);
	memmove_s(indices, size, i.data(), size);
	m_pIndex->Unlock();
}

void Cube::_loadTexture(const std::wstring& strFile)
{
	D3DXCreateTextureFromFile(m_pDevice, strFile.c_str(), &m_pTexture);
}

bool Cube::_initVertexShader()
{
	if (!m_pDevice)
		return false;

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
	if (!m_pDevice)
		return false;

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