#include "Object.h"

Object::Object(const Elite::FPoint3& position, Material* pMat)
	: m_Origin{ position }
	, m_pMaterial{pMat}
{
}

const Material* Object::GetMaterial() const
{
	return m_pMaterial;
}

void Object::Rotate()
{
}
