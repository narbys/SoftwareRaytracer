#pragma once
#include "Scene.h"
class SceneManager
{
public:
	static SceneManager* GetInstance();
	~SceneManager();
	static void Cleanup();
	void AddScene(Scene* pScene);
	Scene* GetScene(int idx) const;
	Scene* GetActiveScene()const;
	void NextScene();
	void PreviousScene();
private:
	SceneManager();	
	static SceneManager* m_pInstance;
	std::vector<Scene*> m_pScenes;
	int m_ActiveIdx;
};

