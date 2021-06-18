#include "SceneManager.h"
SceneManager* SceneManager::m_pInstance{ nullptr };

SceneManager* SceneManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SceneManager();
	}
	return m_pInstance;
}

SceneManager::~SceneManager()
{
	for (Scene* s : m_pScenes)
	{
		delete s;
		s = nullptr;
	}
}
void SceneManager::Cleanup()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
void SceneManager::AddScene(Scene* pScene)
{
	m_pScenes.push_back(pScene);
}
Scene* SceneManager::GetScene(int idx) const
{
	return m_pScenes[idx];
}
Scene* SceneManager::GetActiveScene() const
{
	return m_pScenes[m_ActiveIdx];
}
void SceneManager::NextScene()
{
	if (m_ActiveIdx < m_pScenes.size()-1)
	{
		m_ActiveIdx++;
	}
}
void SceneManager::PreviousScene()
{
	if (m_ActiveIdx > 0)
	{
		m_ActiveIdx--;
	}
}

SceneManager::SceneManager()
	: m_ActiveIdx{}
{
}
