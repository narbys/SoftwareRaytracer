#pragma once
#include "Object.h"

enum class Cullmode
{
	noCulling,
	backfaceCulling,
	frontfaceCulling
};
class Triangle final : public Object
{

public:
	Triangle(const Elite::FPoint3& position, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, Cullmode cullmode,  Material* pMat);
	Triangle(const Elite::FMatrix4& translation, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2,  Cullmode cullmode, Material* pMat);
	virtual ~Triangle();
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shading = false)const override;
	virtual void Rotate() override;
private:
	Elite::FMatrix4 m_TransMat;
	Elite::FVector3 m_Normal;
	Elite::FPoint4 m_V0;
	Elite::FPoint4 m_V1;
	Elite::FPoint4 m_V2;
	Cullmode m_Cullmode;

	float m_Angle;
};
