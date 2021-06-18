#include "Material_Lambert.h"
Material_Lambert::Material_Lambert(float diffReflect, const Elite::RGBColor& diffColor)
	: Material(diffReflect, diffColor)
{
}

Material_Lambert::~Material_Lambert()
{
}

Elite::RGBColor Material_Lambert::Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor);
}
