#include "Plane.h"

Plane::Plane(const Elite::FPoint3& position,Material* pMat, const Elite::FVector3& normal)
	: Object(position,pMat)
	, m_Normal{normal}
{
}

Plane::~Plane()
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord,bool shading) const
{
	const float t = Elite::Dot((m_Origin - ray.origin), m_Normal) / Elite::Dot(ray.direction, m_Normal);
	if (t > ray.tMin && t < ray.tMax)
	{
		const Elite::FPoint3 p = ray.origin + t * ray.direction;
		if (t<hitRecord.tValue)
		{
			hitRecord.hitPoint = p;
			hitRecord.tValue = t;
			hitRecord.normal = m_Normal;
			return true;
		}
	}
	return false;
}
