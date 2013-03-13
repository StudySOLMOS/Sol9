#include "PCH.h"
#include "Texture.h"

Texture::Texture(IDirect3DTexture9* pTexture)
	: m_pTexture(pTexture)
{
}

Texture::~Texture()
{
	if (m_pTexture)
		m_pTexture->Release();
}

IDirect3DBaseTexture9* Texture::getTexture()
{
	return m_pTexture;
}
