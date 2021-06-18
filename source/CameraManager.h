#pragma once
#include "Camera.h"
#include <vector>
class CameraManager
{
public:
	static CameraManager* GetInstance();
	~CameraManager();
	static void Cleanup();
	void AddCamera(Camera* pScene);
	Camera* GetCamera(int idx);
	Camera* GetActiveCamera();
private:
	CameraManager();
	std::vector<Camera*> m_pCameras;	
	static CameraManager* m_pInstance;
	int m_ActiveIdx;
};

