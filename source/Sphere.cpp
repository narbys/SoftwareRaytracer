#include "Sphere.h"

Sphere::Sphere(const Elite::FPoint3& center, Material* pMat, float radius)
	: Object( center, pMat )
	, m_Radius{ radius }
	, m_InvRadius{1/m_Radius}
{
}

Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord, bool shading) const
{
	const Elite::FVector3 rayToSphere{ ray.origin - m_Origin };
	const float a = 1;
	const float b = Elite::Dot(2 * ray.direction, rayToSphere);
	const float c = Elite::Dot(rayToSphere, rayToSphere)-m_Radius*m_Radius;
	const float discriminant = b*b - 4 * a * c;

	if (discriminant < 0.00001f)	return false;

	const float t = (-b - sqrt(discriminant)) * (0.5f * a);
	if (t > ray.tMin && t<hitRecord.tValue)
	{
		if (shading)
			return true;
		hitRecord.hitPoint = ray.origin + t * ray.direction;
		hitRecord.tValue = t;
		hitRecord.normal =  Elite::FVector3{ hitRecord.hitPoint - m_Origin } * m_InvRadius;
		return true;
	}
	return false;
}