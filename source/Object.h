#pragma once
#include "EMath.h"
#include "Ray.h"
#include "HitRecord.h"
#include "ERGBColor.h"
#include "Material.h"
class Object
{
public:
	Object(const Elite::FPoint3& position, Material* pMat);
	Object(const Object& obj)=delete;
	Object(Object&& obj) = delete;
	Object& operator=(const Object& obj) = delete;
	Object& operator=(Object&& obj) = delete;
	virtual ~Object()=default;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shading=false)const=0;
	const Material* GetMaterial()const;
	virtual void Rotate();
protected:
	Elite::FPoint3 m_Origin;
	Material* m_pMaterial;
};