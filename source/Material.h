#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "HitRecord.h"
#include "BRDF.h"
class Material
{
public:
	Material(float diffReflect, const Elite::RGBColor& diffColor = {0, 0, 0});
	virtual ~Material();
	virtual Elite::RGBColor Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir)const=0;
protected:
	float m_DiffuseReflectance;
	Elite::RGBColor m_DiffuseColor;
};