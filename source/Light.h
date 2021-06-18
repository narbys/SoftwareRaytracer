#pragma once
#include "EMath.h"
#include "ERGBColor.h"
//#include "HitRecord.h"
class Light
{
public:
	Light(const Elite::RGBColor& color, float intensity);
	virtual ~Light();
	virtual Elite::RGBColor CalculateIrradiance(const Elite::FPoint3& pointToShade) const = 0;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint)const = 0;
	virtual Elite::FVector3 GetLightVector(const Elite::FPoint3& hitPoint) const = 0;
	void Toggle();
protected:
	Elite::RGBColor m_LightColor;
	float m_Intensity;
	bool m_IsOn{true};
};