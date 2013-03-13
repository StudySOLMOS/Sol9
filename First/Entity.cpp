#include "PCH.h"
#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"

Entity::Entity(Mesh* pMesh)
	: m_pOwnerMesh(pMesh), m_matLocal()
{
	D3DXMatrixIdentity(&m_matLocal);
}

Entity::~Entity()
{
	if (m_pOwnerMesh)
		delete m_pOwnerMesh;
}

void Entity::update(unsigned int timeMs)
{
	D3DXVECTOR3 vRotate(2.0f, 1.5f, 2.0f);
	vRotate *= (float)timeMs / 1000.0f;

	D3DXMATRIX matTemp;
	D3DXMatrixRotationYawPitchRoll(&matTemp, vRotate.y, vRotate.x, vRotate.z);
	m_matLocal = matTemp * m_matLocal;
}

void Entity::render(IDirect3DDevice9* pDevice)
{
	if (!pDevice)
		return;

	if (!m_pOwnerMesh)
		return;

	pDevice->SetTransform(D3DTS_WORLD, &m_matLocal);

	m_pOwnerMesh->render(pDevice);
}

void Entity::setTexture(u32 nLayer, Texture* pTexture)
{
	if (!pTexture)
		return;

	if (!m_pOwnerMesh || m_pOwnerMesh->getMeshBufferCount() < nLayer)
		return;

	m_pOwnerMesh->getMeshBuffer(nLayer)->setTexture(pTexture);
}