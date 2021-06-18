#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& color, float intensity)
	: m_Direction{direction}
	, Light(color,intensity)
{
}

DirectionalLight::~DirectionalLight()
{
}

Elite::RGBColor DirectionalLight::CalculateIrradiance(const Elite::FPoint3& pointToShade) const
{
	if (!m_IsOn)
		return Elite::RGBColor();
	const Elite::RGBColor ergb = m_LightColor*m_Intensity;
	return ergb;
}

Elite::FVector3 DirectionalLight::GetDirection(const Elite::FPoint3& hitPoint) const
{
	return m_Direction;
}

Elite::FVector3 DirectionalLight::GetLightVector(const Elite::FPoint3& hitPoint) const
{
	return m_Direction;
}
