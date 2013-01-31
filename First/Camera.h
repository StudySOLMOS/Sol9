#pragma once

class Camera
{
protected:
	IDirect3DDevice9* m_pDevice;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProjection;

public:
	Camera(IDirect3DDevice9* pDevice);
	virtual ~Camera();

	virtual void init(const D3DXVECTOR3& vEye, const D3DXVECTOR3& vLookAt, const D3DXVECTOR3& vUp);
};