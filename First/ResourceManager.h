#pragma once

#include "ReferenceCounter.h"
#include "Singleton.h"

class Resource : public ReferenceCounter
{
private:
public:
	Resource();
	virtual ~Resource();
};

class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::map<std::string, Resource*> m_ResourceMap;

public:
	ResourceManager();
	~ResourceManager();

	Resource* createTexture(IDirect3DDevice9* pDevice, const std::string& strFileName);
};