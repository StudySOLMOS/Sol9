#include "PCH.h"
#include "ResourceManager.h"
#include "Texture.h"

Resource::Resource()
{
}

Resource::~Resource()
{
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	auto remove = [](std::map<std::string, Resource*>::value_type v)
	{
		if (v.second)
			v.second->detach();
	};

	std::for_each(m_ResourceMap.begin(), m_ResourceMap.end(), remove);
	m_ResourceMap.clear();
}

Resource* ResourceManager::createTexture(IDirect3DDevice9* pDevice, const std::string& strFileName)
{
	auto iter = m_ResourceMap.find(strFileName);
	if (iter != m_ResourceMap.end())
		return iter->second;

	IDirect3DTexture9* texture = nullptr;
	D3DXCreateTextureFromFileA(pDevice, strFileName.c_str(), &texture);

	Resource* pTexture = new Texture(texture);
	m_ResourceMap.insert(std::pair<std::string, Resource*>(strFileName, pTexture));
	return pTexture;
}