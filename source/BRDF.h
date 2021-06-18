#pragma once
#include "EMath.h"
#include "ERGBColor.h"
namespace BRDF
{
	const Elite::RGBColor Lambert(float reflectance, const Elite::RGBColor& color);
	const Elite::RGBColor Lambert(const Elite::RGBColor& reflectance, const Elite::RGBColor& color);

	const Elite::RGBColor Phong(float specularReflectance, float phongExponent, 
		const Elite::FVector3& lightDir, const Elite::FVector3& viewDir, const Elite::FVector3& normal);

	const Elite::RGBColor CookTorrance(const Elite::RGBColor f0, float roughness, bool metalness,
		const Elite::FVector3& lightDir, const Elite::FVector3& viewDir, const Elite::FVector3& normal, const Elite::FVector3& halfVect);
	const Elite::RGBColor Fresnel(const Elite::FVector3& h, const Elite::FVector3& v, const Elite::RGBColor& f0);
}