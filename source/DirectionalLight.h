#pragma once
#include "Light.h"
class DirectionalLight final : public Light
{
public:
	DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& color, float intensity);
	virtual ~DirectionalLight();
	virtual Elite::RGBColor CalculateIrradiance(const Elite::FPoint3& pointToShade) const override;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint)const override;
	virtual Elite::FVector3 GetLightVector(const Elite::FPoint3& hitPoint) const override;
private:
	Elite::FVector3 m_Direction;
};