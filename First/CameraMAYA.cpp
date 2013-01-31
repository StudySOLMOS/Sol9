#include "stdafx.h"
#include "CameraMAYA.h"

CameraMAYA::CameraMAYA(IDirect3DDevice9* pDevice)
	: Camera(pDevice), m_MouseState(), r()
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
	D3DXMatrixIdentity(&r);
}

void CameraMAYA::update(unsigned int timeMs)
{
	if (m_MouseState.r)
	{
		D3DXVECTOR3 v = (m_MouseState.prev - m_MouseState.curr) * (float)timeMs / 1000.0f;
		D3DXVECTOR3 vv(0.0f, -v.x, v.z);
		rotation(vv);
		m_MouseState.prev = m_MouseState.curr;
		
		//D3DXVECTOR3 v = (m_MouseState.prev - m_MouseState.curr) * (float)timeMs / 1000.0f;
		//D3DXVECTOR3 vv(0.0f, -v.x, v.z);

		//D3DXMATRIX m;
		//D3DXMatrixRotationYawPitchRoll(&m, vv.x, vv.z, vv.y);

		//r *= m;
		//m_matView = r * m_matView;
		////m_matView *= m;
		//m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

		//m_MouseState.prev = m_MouseState.curr;
	}
	else if (m_MouseState.m)
	{
		D3DXVECTOR3 v = m_MouseState.prev - m_MouseState.curr;
		translation(v);
		m_MouseState.prev = m_MouseState.curr;
	}
}

void CameraMAYA::message(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_RBUTTONDOWN :
		m_MouseState.r = true;
		m_MouseState.prev = D3DXVECTOR3((float)LOWORD(lParam), 0.0f, -(float)HIWORD(lParam));
		break;

	case WM_RBUTTONUP :
		m_MouseState.r = false;
		D3DXMatrixIdentity(&r);
		break;

	case WM_MBUTTONDOWN :
		m_MouseState.m = true;
		m_MouseState.prev = D3DXVECTOR3((float)LOWORD(lParam), 0.0f, -(float)HIWORD(lParam));
		break;

	case WM_MBUTTONUP :
		m_MouseState.m = false;
		break;

	case WM_MOUSEHWHEEL :
		//{
		//	int d = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		//	D3DXVECTOR3 z(m_matView._31, m_matView._32, m_matView._33);
		//	translation(z * (float)d * 15.0f);
		//}
		break;

	case WM_MOUSEMOVE :
		m_MouseState.curr = D3DXVECTOR3((float)LOWORD(lParam), 0.0f, -(float)HIWORD(lParam));
		break;
	}

	return;
}