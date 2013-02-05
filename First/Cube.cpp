#include "PCH.h"
#include "Cube.h"

Cube::Cube(IDirect3DDevice9* pDevice, float fSize, const std::string& strFile)
	: m_pDevice(pDevice)
	, m_pVertex(nullptr), m_pIndex(nullptr), m_pTexture(nullptr)
	, m_matLocal()
{
	D3DXMatrixIdentity(&m_matLocal);

	_setupMesh(fSize);
	_loadTexture(strFile);
}

Cube::~Cube()
{
	if (m_pVertex)
		m_pVertex->Release();

	if (m_pIndex)
		m_pIndex->Release();

	if (m_pTexture)
		m_pTexture->Release();
}

void Cube::update(unsigned int timeMs)
{
	D3DXVECTOR3 vRotate(2.0f, 1.5f, 2.0f);
	vRotate *= (float)timeMs / 1000.0f;

	D3DXMATRIX matTemp;
	D3DXMatrixRotationYawPitchRoll(&matTemp, vRotate.y, vRotate.x, vRotate.z);
	m_matLocal = matTemp * m_matLocal;
}

void Cube::render()
{
	if (!m_pDevice)
		return;

	if (!m_pVertex || !m_pIndex)
		return;

	m_pDevice->SetTransform(D3DTS_WORLD, &m_matLocal);

	if (m_pTexture)
		m_pDevice->SetTexture(0, m_pTexture);

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
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 1, 0, 0, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 1, 0, 0, 1));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 1, 0, 1, 1));
	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 1, 0, 1, 0));

	v.push_back(VERTEX(-fSize, fSize, fSize, 0, 0, 1, 0, 0));
	v.push_back(VERTEX(fSize, fSize, fSize, 0, 0, 1, 0, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, 0, 1, 1, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, 0, 1, 1, 0));

	v.push_back(VERTEX(-fSize, fSize, -fSize, -1, 0, 0, 0, 0));
	v.push_back(VERTEX(-fSize, fSize, fSize, -1, 0, 0, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, -1, 0, 0, 1, 1));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, -1, 0, 0, 1, 0));

	v.push_back(VERTEX(fSize, fSize, fSize, 1, 0, 0, 0, 0));
	v.push_back(VERTEX(fSize, fSize, -fSize, 1, 0, 0, 0, 1));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 1, 0, 0, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 1, 0, 0, 1, 0));

	v.push_back(VERTEX(fSize, fSize, -fSize, 0, 0, -1, 0, 0));
	v.push_back(VERTEX(-fSize, fSize, -fSize, 0, 0, -1, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, 0, -1, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, 0, -1, 1, 0));

	v.push_back(VERTEX(fSize, -fSize, -fSize, 0, -1, 0, 0, 0));
	v.push_back(VERTEX(-fSize, -fSize, -fSize, 0, -1, 0, 0, 1));
	v.push_back(VERTEX(-fSize, -fSize, fSize, 0, -1, 0, 1, 1));
	v.push_back(VERTEX(fSize, -fSize, fSize, 0, -1, 0, 1, 0));

	m_pDevice->CreateVertexBuffer(sizeof(VERTEX) * v.size(), 0, VERTEX::FVF, D3DPOOL_MANAGED, &m_pVertex, nullptr);
	
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

	m_pDevice->CreateIndexBuffer(sizeof(INDEX) * i.size(), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndex, nullptr);

	size = sizeof(INDEX) * i.size();
	void* indices;
	m_pIndex->Lock(0, sizeof(INDEX) * i.size(), &indices, 0);
	memmove_s(indices, size, i.data(), size);
	m_pIndex->Unlock();
}

void Cube::_loadTexture(const std::string& strFile)
{
	D3DXCreateTextureFromFileA(m_pDevice, strFile.c_str(), &m_pTexture);

	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}
