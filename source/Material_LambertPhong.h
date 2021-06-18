#pragma once
#include "Material.h"
class Material_LambertPhong : public Material
{
public:
	Material_LambertPhong(float diffReflect, const Elite::RGBColor& diffColor, float specularReflect, float phongExponent);
	virtual ~Material_LambertPhong();
	virtual Elite::RGBColor Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir)const override;
private:
	float m_SpecularReflectance;
	float m_PhongExponent;
};