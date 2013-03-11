#pragma once

class Texture;

class Resource
{
private:
public:
	Resource();
	virtual ~Resource();
};

class ResourceManager
{
private:
	IDirect3DDevice9* m_pDevice;
	std::map<std::string, Resource*> m_ResourceMap;

public:
	ResourceManager(IDirect3DDevice9* pDevice);
	~ResourceManager();

	Resource* createTexture(const std::string& strFileName);
};