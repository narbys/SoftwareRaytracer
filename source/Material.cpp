#include "Material.h"

Material::Material(float diffReflect, const Elite::RGBColor& diffColor)
	: m_DiffuseReflectance{diffReflect}
	, m_DiffuseColor{diffColor}
{
}

Material::~Material()
{
}
