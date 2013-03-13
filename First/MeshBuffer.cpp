#include "PCH.h"
#include "MeshBuffer.h"
#include "Texture.h"

MeshBuffer::MeshBuffer()
	: m_pVertex(nullptr), m_pIndex(nullptr), m_pTexture(nullptr)
	, m_nVertices(0), m_nIndices(0)
{
}

MeshBuffer::~MeshBuffer()
{
	if (m_pVertex)
		m_pVertex->Release();

	if (m_pIndex)
		m_pIndex->Release();

	if (m_pTexture)
		m_pTexture->detach();
}

void MeshBuffer::render(IDirect3DDevice9* pDevice)
{
	if (!pDevice)
		return;

	if (!m_pVertex || !m_pIndex)
		return;

	if (m_pTexture && m_pTexture->getTexture())
		pDevice->SetTexture(0, m_pTexture->getTexture());

	pDevice->SetMaterial(&m_Material);
	pDevice->SetStreamSource(0, m_pVertex, 0, sizeof(VERTEX));
	pDevice->SetFVF(VERTEX::FVF);
	pDevice->SetIndices(m_pIndex);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVertices, 0, m_nIndices);
}

void MeshBuffer::setTexture(Texture* pTexture)
{
	if (!pTexture)
		return;

	m_pTexture = pTexture;
	pTexture->attach();
}

void MeshBuffer::setMaterial(const D3DMATERIAL9& Material)
{
	m_Material = Material;
}