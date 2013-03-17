#include "PCH.h"
#include "First.h"
#include "CameraMAYA.h"
#include "TimeManager.h"
#include "GeometryCreator.h"
#include "ResourceManager.h"

const std::wstring g_strTitle = L"First by.Sol9";
const unsigned int g_nWidth = 800;
const unsigned int g_nHeight = 600;

IDirect3DDevice9* g_pd3dDevice = nullptr;
ID3DXFont* g_pd3dFont = nullptr;
Camera* g_pCamera = nullptr;
Entity* g_pCube = nullptr;

int g_nFPS = 0;
int g_nFrame = 0;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

void initialize();
void cleanup();
void update(unsigned int timeMs);
void render();

int main()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FIRST);
	wcex.lpszClassName	= g_strTitle.c_str();

	if (!RegisterClassEx(&wcex))
		return 0;

	HWND hWnd = CreateWindow(g_strTitle.c_str(), g_strTitle.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
		return 0;

	RECT rect = {0, 0, g_nWidth, g_nHeight};
	AdjustWindowRect(&rect, wcex.style, TRUE);
	SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	IDirect3D9* d3d = Direct3DCreate9(D3D9b_SDK_VERSION);

	if (!d3d)
		return 0;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.hDeviceWindow					= hWnd;
	d3dpp.BackBufferWidth				= rect.right;
	d3dpp.BackBufferHeight				= rect.bottom;
	d3dpp.BackBufferFormat				= D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount				= 1;
	d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality			= 0;
	d3dpp.Windowed						= TRUE;
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil		= TRUE;

	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
		return 0;

	d3d->Release();

	if (FAILED(D3DXCreateFont(g_pd3dDevice, 12, 6, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, L"frquad", &g_pd3dFont)))
		return 0;

	initialize();

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			TimeManager* pTimeManager = TimeManager::instance();
			static unsigned int before = pTimeManager->time();
			unsigned int current = pTimeManager->time();
			unsigned int tick = current - before;

			update(tick);
			render();

			before = current;

			static unsigned int time = 0;
			time += tick;

			if (time >= 1000)
			{
				g_nFPS = g_nFrame;
				g_nFrame = 0;

				time -= 1000;
			}
		}
	}

	cleanup();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pCamera)
		g_pCamera->message(hWnd, Msg, wParam, lParam);

	switch (Msg)
	{
	case WM_COMMAND :
		switch (LOWORD(wParam))
		{
		case IDM_EXIT :
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}
		break;

	case WM_KEYDOWN :
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;

	case WM_DESTROY :
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}

const int tile = 255;

void initialize()
{
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(D3DLIGHT9));
	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Diffuse.r = 0.7f;
	Light.Diffuse.g = 0.7f;
	Light.Diffuse.b = 0.7f;
	Light.Ambient.r = 0.5f;
	Light.Ambient.g = 0.5f;
	Light.Ambient.b = 0.5f;
	Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_pd3dDevice->SetLight(0, &Light);
	g_pd3dDevice->LightEnable(0, TRUE);

	g_pCamera = new Camera(g_pd3dDevice);
	g_pCamera->init(D3DXVECTOR3(0.0f, 300.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	GeometryCreator creator(g_pd3dDevice);

	g_pCube = new Entity(creator.createCube(60.0f));
	g_pCube->setTexture(0, (Texture*)ResourceManager::instance()->createTexture(g_pd3dDevice, "image.jpg"));
}

void cleanup()
{
	if (g_pCube)
		delete g_pCube;

	if (g_pCamera)
		delete g_pCamera;

	if (g_pd3dFont)
		g_pd3dFont->Release();

	if (g_pd3dDevice)
		g_pd3dDevice->Release();
}

void update(unsigned int timeMs)
{
	g_pCube->update(timeMs);
	g_pCamera->update(timeMs);
}

void render()
{
	g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(240, 240, 240), 1.0f, 0);
	g_pd3dDevice->BeginScene();

	g_pCube->render(g_pd3dDevice);

	if (g_nFrame != g_nFPS)
	{
		std::wstringstream temp;
		temp << L"  fps = " << g_nFPS;

		RECT r = {0, 10, 120, 40};
		g_pd3dFont->DrawText(nullptr, temp.str().c_str(), -1, &r, 0, D3DCOLOR_XRGB(0, 0, 0));
	}

	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

	++g_nFrame;
}
