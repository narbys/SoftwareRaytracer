#pragma once
#include "Material.h"
class Material_Lambert : public Material
{
public:
	Material_Lambert(float diffReflect, const Elite::RGBColor& diffColor);
	~Material_Lambert();
	virtual Elite::RGBColor Shade(const HitRecord& hitPoint, const Elite::FVector3& lightDir, const Elite::FVector3& viewDir)const override;
private:

};