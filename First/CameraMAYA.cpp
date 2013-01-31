#include "stdafx.h"
#include "CameraMAYA.h"

CameraMAYA::CameraMAYA(IDirect3DDevice9* pDevice)
	: Camera(pDevice)
{
}

CameraMAYA::~CameraMAYA()
{
}

void CameraMAYA::init(const D3DXVECTOR3& vEye, const D3DXVECTOR3& vLookAt, const D3DXVECTOR3& vUp)
{
	if (!m_pDevice)
		return;

	Camera::init(vEye, vLookAt, vUp);
}
