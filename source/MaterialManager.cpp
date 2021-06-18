#include "MaterialManager.h"
#include "Material.h"
MaterialManager* MaterialManager::m_pInstance{ nullptr };

MaterialManager* MaterialManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MaterialManager();
	}
	return m_pInstance;
}

MaterialManager::~MaterialManager()
{
	for (Material* m : m_pMaterials)
	{
		delete m;
		m = nullptr;
	}
}

void MaterialManager::Cleanup()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

Material* MaterialManager::AddMaterial(Material* mat)
{
	m_pMaterials.push_back(mat);
	return m_pMaterials.back();
}

MaterialManager::MaterialManager()
{
}