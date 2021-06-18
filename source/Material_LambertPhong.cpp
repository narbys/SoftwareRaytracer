#include "Material_LambertPhong.h"

Material_LambertPhong::Material_LambertPhong(float diffReflect, const Elite::RGBColor& diffColor, float specularReflect, float phongExponent)
	: Material(diffReflect, diffColor)
	, m_SpecularReflectance{specularReflect}
	, m_PhongExponent{phongExponent}
{
}

Material_LambertPhong::~Material_LambertPhong()
{
}

Elite::RGBColor Material_LambertPhong::Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor) 
		+ BRDF::Phong(m_SpecularReflectance, m_PhongExponent, lightDir, viewDir, hitPoint.normal);
}
