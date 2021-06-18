#pragma once
#include <vector>
class Material;
class MaterialManager
{
public:
	static MaterialManager* GetInstance();
	~MaterialManager();
	static void Cleanup();
	Material* AddMaterial(Material* mat);

private:
	MaterialManager();
	static MaterialManager* m_pInstance;
	std::vector<Material*> m_pMaterials;
};