#include "Material_CookTorrance.h"


Material_CookTorrance::Material_CookTorrance(const Elite::RGBColor& albedoColor, bool metalness, float roughness, float specReflect,
	float diffReflect)
	: Material(diffReflect)
	, m_F0{ }
	, m_Roughness{ roughness }
	, m_SpecularReflectance{ specReflect }
	, m_Metalness{ metalness }
{
	if (m_Metalness == false)
		m_F0 = Elite::RGBColor(0.04f, 0.04f, 0.04f);
	else
		m_F0 = albedoColor;
}

Material_CookTorrance::~Material_CookTorrance()
{
}

Elite::RGBColor Material_CookTorrance::Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir) const
{
	const Elite::FVector3 halfVect = Elite::GetNormalized(viewDir + lightDir);
	const Elite::RGBColor cookTorranceBRDF = BRDF::CookTorrance(m_F0, m_Roughness, m_Metalness, lightDir, viewDir, hitPoint.normal, halfVect);

	Elite::RGBColor kd{ 0.f,0.f,0.f };
	if (m_Metalness == false)
		kd =(Elite::RGBColor(1, 1, 1) - BRDF::Fresnel(halfVect, viewDir, m_F0));
	return BRDF::Lambert(m_DiffuseReflectance,kd) + cookTorranceBRDF;
}
