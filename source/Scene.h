#pragma once
#include <vector>
#include "Object.h"
#include "Light.h"
class Scene
{
public:
	Scene();
	~Scene();
	void AddObject(Object* pObj);
	void AddLight(Light* pLight);
	const std::vector<Object*>& GetObjectsInScene() const;
	const std::vector<Light*>& GetLightsInScene() const;
private:
	std::vector<Object*> m_pObjects;
	std::vector<Light*> m_pLights;
};