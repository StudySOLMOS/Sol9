#pragma once

#include "ReferenceCounter.h"

class Mesh;

class ColladaLoader : public ReferenceCounter
{
private:
public:
	ColladaLoader();
	~ColladaLoader();

	Mesh* loadMesh(const std::string& strFileName);

private:
};