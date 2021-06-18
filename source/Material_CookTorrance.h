#pragma once
#include "Material.h"
class Material_CookTorrance : public Material
{
public:
	Material_CookTorrance(const Elite::RGBColor& albedoColor, bool metalness, float roughness, float specReflect,
		float diffReflect);
	virtual ~Material_CookTorrance();
	virtual Elite::RGBColor Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir)const override;
private:
	Elite::RGBColor m_F0;	
	const float m_Roughness;
	const float m_SpecularReflectance;
	const bool m_Metalness;
};