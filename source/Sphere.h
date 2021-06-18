#pragma once
#include "Object.h"
class Sphere final : public Object
{
public:
	Sphere(const Elite::FPoint3& center,Material* pMat , float radius);
	virtual ~Sphere();
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool shading = false)const override;
	//virtual const Elite::FVector3 GetNormal(const Elite::FPoint3& point) const override;
private:
	float m_Radius;
	const float m_InvRadius;
	//Elite::RGBColor m_Color;
};