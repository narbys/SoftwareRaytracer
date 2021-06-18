#include "PointLight.h"

PointLight::PointLight(const Elite::FPoint3& pos, const Elite::RGBColor& color, float intensity)
	: m_Position{pos}
	, Light(color, intensity)
{
}

PointLight::~PointLight()
{
}

Elite::RGBColor PointLight::CalculateIrradiance(const Elite::FPoint3& pointToShade) const
{
	if (!m_IsOn)
		return Elite::RGBColor();
	const Elite::RGBColor ergb = m_LightColor * m_Intensity / Elite::SqrMagnitude(m_Position- pointToShade);
	return ergb;
}

Elite::FVector3 PointLight::GetDirection(const Elite::FPoint3& hitPoint) const
{
	Elite::FVector3 h{ m_Position - hitPoint };
	//Elite::GetNormalized(h);
	
	return Elite::InvSqrtFst(Elite::Dot(h,h))*h;		//normalise but 1/3 more performant
}

Elite::FVector3 PointLight::GetLightVector(const Elite::FPoint3& hitPoint) const
{
	Elite::FVector3 h{ m_Position - hitPoint };

	return h;
}
