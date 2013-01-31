#pragma once

#include "Camera.h"

class CameraMAYA : public Camera
{
public:
	CameraMAYA(IDirect3DDevice9* pDevice);
	virtual ~CameraMAYA();

	virtual void init(const D3DXVECTOR3& vEye, const D3DXVECTOR3& vLookAt, const D3DXVECTOR3& vUp);
};