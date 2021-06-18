#pragma once
#include "Object.h"
class Plane final : public Object
{
public:
	Plane(const Elite::FPoint3& position, Material* pMat, const Elite::FVector3& normal);
	virtual ~Plane();
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool shading = false)const override;
	//virtual const Elite::FVector3 GetNormal(const Elite::FPoint3& point) const override;
private:
	Elite::FVector3 m_Normal;
};