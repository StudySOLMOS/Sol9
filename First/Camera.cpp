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

void Camera::update(unsigned int timeMs)
{
}

void Camera::message(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return;
}

void Camera::translation(const D3DXVECTOR3& vTranslate)
{
	D3DXMATRIX temp;
	D3DXMatrixTranslation(&temp, vTranslate.x, vTranslate.y, vTranslate.z);
	m_matView = temp * m_matView;

	m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void Camera::rotation(const D3DXVECTOR3& vRotate)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationYawPitchRoll(&temp, vRotate.y, vRotate.x, vRotate.z);
	m_matView = temp * m_matView;

	m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void Camera::scaling(const D3DXVECTOR3& vScale)
{
}
