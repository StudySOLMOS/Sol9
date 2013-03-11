#pragma once

#include "ResourceManager.h"

class Texture : public Resource
{
private:
	IDirect3DTexture9* m_pTexture;

public:
	Texture(IDirect3DTexture9* pTexture);
	virtual ~Texture();

	IDirect3DBaseTexture9* getTexture();
};