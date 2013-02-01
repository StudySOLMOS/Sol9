#pragma once

class Mesh;

class Entity
{
private:
	Mesh* m_pOwnerMesh;

public:
	Entity();
	virtual ~Entity();
};