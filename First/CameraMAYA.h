#pragma once

#include "Camera.h"

class CameraMAYA : public Camera
{
private:
	struct MouseState
	{
		bool l;
		bool r;
		bool m;
		D3DXVECTOR3 prev;
		D3DXVECTOR3 curr;

		MouseState()
			: l(false), r(false), m(false)
			, prev(0.0f, 0.0f, 0.0f), curr(0.0f, 0.0f, 0.0f) {}
	};
	MouseState m_MouseState;

	D3DXMATRIX r;

public:
	CameraMAYA(IDirect3DDevice9* pDevice);
	virtual ~CameraMAYA();

	virtual void init(const D3DXVECTOR3& vEye, const D3DXVECTOR3& vLookAt, const D3DXVECTOR3& vUp);
	virtual void update(unsigned int timeMs);

	virtual void message(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};