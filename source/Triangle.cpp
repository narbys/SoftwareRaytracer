#include "Triangle.h"

Triangle::Triangle(const Elite::FPoint3& position, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2,  Cullmode cullmode, Material* pMat)
	: Object(Elite::FPoint3{ ((v0.x + v1.x + v2.x) / 3),((v0.y + v1.y + v2.y) / 3),((v0.z + v1.z + v2.z) / 3) }, pMat)
	, m_Normal{}
	, m_V0{ v0 }
	, m_V1{ v1 }
	, m_V2{ v2 }
	, m_Cullmode{cullmode}
{
	m_TransMat.Identity();
	m_TransMat = Elite::MakeTranslation(position - m_Origin);
	m_V0 = m_TransMat * Elite::FPoint4(v0);
	m_V1 = m_TransMat * Elite::FPoint4(v1);
	m_V2 = m_TransMat * Elite::FPoint4(v2);
	m_Origin = (m_TransMat * Elite::FPoint4(m_Origin)).xyz;

	const Elite::FVector3 a = v1 - v0;
	const Elite::FVector3 b = v2 - v0;
	m_Normal = Elite::Cross(a, b);
}

Triangle::Triangle(const Elite::FMatrix4& translation, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2,  Cullmode cullmode, Material* pMat)
	: Object(Elite::FPoint3{ ((v0.x + v1.x + v2.x) / 3),((v0.y + v1.y + v2.y) / 3),((v0.z + v1.z + v2.z) / 3) }, pMat)
	, m_Normal{}
	, m_V0{ v0 }
	, m_V1{ v1 }
	, m_V2{ v2 }
	, m_TransMat{ m_TransMat.Identity() }
	, m_Cullmode{cullmode}
{

	m_TransMat = translation;
	m_V0 = translation * Elite::FPoint4(v0);
	m_V1 = translation * Elite::FPoint4(v1);
	m_V2 = translation * Elite::FPoint4(v2);
	m_Origin = (m_TransMat * Elite::FPoint4(m_Origin)).xyz;

	const Elite::FVector3 a = v1 - v0;
	const Elite::FVector3 b = v2 - v0;
	m_Normal = Elite::Cross(a, b);
}

Triangle::~Triangle()
{
}

void Triangle::Rotate()
{
	const Elite::FMatrix4 backToZero = Elite::MakeTranslation(Elite::FPoint3(0,0,0) - m_Origin);
	const Elite::FMatrix4 rotMat = Elite::MakeRotationY(m_Angle);
	const Elite::FMatrix4 pointRotation =  m_TransMat * rotMat * backToZero;
	m_V0 = pointRotation * m_V0;
	m_V1 = pointRotation * m_V1;
	m_V2 = pointRotation * m_V2;
	m_Origin = (pointRotation * Elite::FPoint4(m_Origin)).xyz;
	m_Normal = (rotMat * Elite::FVector4(m_Normal)).xyz;
	m_Angle = 0.1f;
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitRec, bool shading) const
{
	const Elite::FVector3 viewDir = ray.direction;
	if (Elite::Dot(m_Normal, viewDir) == 0)
		return false;
	//cullmode switch
	switch (m_Cullmode)
	{
	case Cullmode::noCulling:
		break;
	case Cullmode::backfaceCulling:
		if (!shading)
		{
			if (Elite::Dot(m_Normal, viewDir) > 0)
				return false;
		}
		else
		{
			if (Elite::Dot(m_Normal, viewDir) < 0)
				return false;
		}
		break;
	case Cullmode::frontfaceCulling:
		if (!shading)
		{
			if (Elite::Dot(m_Normal, viewDir) < 0)
				return false;
		}
		else
		{
			if (Elite::Dot(m_Normal, viewDir) > 0)
				return false;
		}
		break;
	}

	const Elite::FVector3 L = m_V0.xyz - ray.origin;
	const float t = Elite::Dot(L, m_Normal) / Elite::Dot(viewDir, m_Normal);

	if (t < ray.tMin || t > ray.tMax || t > hitRec.tValue)
		return false;

	const Elite::FPoint3 p = ray.origin + t * viewDir;
	const Elite::FVector3 edgeA = m_V1.xyz - m_V0.xyz;
	Elite::FVector3 pointToSide = p - m_V0.xyz;
	if (Elite::Dot(m_Normal, Elite::Cross(edgeA, pointToSide)) < 0)
		return false;
	const Elite::FVector3 edgeB = m_V2.xyz - m_V1.xyz;
	pointToSide = p - m_V1.xyz;
	if (Elite::Dot(m_Normal, Elite::Cross(edgeB, pointToSide)) < 0)
		return false;
	const Elite::FVector3 edgeC = m_V0.xyz - m_V2.xyz;
	pointToSide = p - m_V2.xyz;
	if (Elite::Dot(m_Normal, Elite::Cross(edgeC, pointToSide)) < 0)
		return false;

	hitRec.hitPoint = p;
	hitRec.normal = m_Normal;
	hitRec.tValue = t;
	return true;
}
