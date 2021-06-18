#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (Object* o : m_pObjects)
	{
		delete o;
		o = nullptr;
	}
	for (Light* l : m_pLights)
	{
		delete l;
		l = nullptr;
	}
}

void Scene::AddObject(Object* pObj)
{

	m_pObjects.push_back(pObj);
}

void Scene::AddLight(Light* pLight)
{
	m_pLights.push_back(pLight);
}

const std::vector<Object*>& Scene::GetObjectsInScene() const
{
	return m_pObjects;
}

const std::vector<Light*>& Scene::GetLightsInScene() const
{
	return m_pLights;
}
