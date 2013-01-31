#include "stdafx.h"
#include "Camera.h"

Camera::Camera(IDirect3DDevice9* pDevice)
	: m_pDevice(pDevice), m_matView(), m_matProjection()
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProjection);
}

Camera::~Camera()
{
}

void Camera::init(const D3DXVECTOR3& vEye, const D3DXVECTOR3& vLookAt, const D3DXVECTOR3& vUp)
{
	if (!m_pDevice)
		return;

	D3DXMatrixLookAtLH(&m_matView, &vEye, &vLookAt, &vUp);
	m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DVIEWPORT9 vp;
	m_pDevice->GetViewport(&vp);
	D3DXMatrixPerspectiveFovLH(&m_matProjection, D3DX_PI/4, (float)vp.Width / (float)vp.Height, 0.1f, 1000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProjection);
}
