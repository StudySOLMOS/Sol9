#include "PCH.h"
#include "Renderer.h"
#include "Mesh.h"

Renderer::Renderer(IDirect3DDevice9* pDevice)
	: m_pDevice(pDevice)
{
}

Renderer::~Renderer()
{
}
