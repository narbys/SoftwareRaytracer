#include "Light.h"

Light::Light(const Elite::RGBColor& color, float intensity)
	: m_LightColor{color}
	, m_Intensity{intensity}
{
}

Light::~Light()
{
}

void Light::Toggle()
{
	m_IsOn = !m_IsOn;
}
