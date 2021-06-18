#pragma once
#include "Light.h"
class PointLight final : public Light
{
public:
	PointLight(const Elite::FPoint3& pos, const Elite::RGBColor& color, float intensity);
	virtual ~PointLight();
	virtual Elite::RGBColor CalculateIrradiance(const Elite::FPoint3& pointToShade) const override;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint)const override;
	virtual Elite::FVector3 GetLightVector(const Elite::FPoint3& hitPoint) const override;
private:
	Elite::FPoint3 m_Position;
};