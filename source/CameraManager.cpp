#include "CameraManager.h"
CameraManager* CameraManager::m_pInstance{ nullptr };
CameraManager* CameraManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CameraManager();
	}
	return m_pInstance;
}

CameraManager::~CameraManager()
{
	for (Camera* pCam : m_pCameras)
	{
		delete pCam;
		pCam = nullptr;
	}
}

void CameraManager::Cleanup()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void CameraManager::AddCamera(Camera* pCam)
{
	m_pCameras.push_back(pCam);
}

Camera* CameraManager::GetCamera(int idx)
{
	return m_pCameras[idx];
}
Camera* CameraManager::GetActiveCamera()
{
	return m_pCameras[m_ActiveIdx];
}
CameraManager::CameraManager()
	: m_ActiveIdx{}
{
}
