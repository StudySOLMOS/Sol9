#include "PCH.h"
#include "MeshBuffer.h"

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
		m_pTexture->Release();
}

void MeshBuffer::render(IDirect3DDevice9* pDevice)
{
	if (!pDevice)
		return;

	if (!m_pVertex || !m_pIndex)
		return;

	if (m_pTexture)
		pDevice->SetTexture(0, m_pTexture);
	
	pDevice->SetStreamSource(0, m_pVertex, 0, sizeof(VERTEX));
	pDevice->SetFVF(VERTEX::FVF);
	pDevice->SetIndices(m_pIndex);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVertices, 0, m_nIndices);
}