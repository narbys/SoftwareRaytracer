#include "BRDF.h"
namespace BRDF
{
	namespace
	{
		//cook torrance functions
		float NormalDistribution(float a, const Elite::FVector3& n, const Elite::FVector3& h)
		{
			//the normal distribution formula (Trowbridge-Reitz GGX)
			const float normalDistribution = (a * a) / (float(E_PI) * Elite::Square(Elite::Square(Elite::Dot(n, h)) * (a * a - 1) + 1));
			return normalDistribution;
		}

		float Geometry(const Elite::FVector3& n, const Elite::FVector3& v, float k)
		{
			//Geometry function Schlick-GGX(Schlick-Beckmann with remapped roughness)
			const float normalDotView = Elite::Dot(n, v);
			const float geometry = normalDotView / (normalDotView * (1 - k) + k);
			return geometry;
		}
		float GeometrySmith(const Elite::FVector3& n, const Elite::FVector3& v, const Elite::FVector3& l, float k)
		{
			//Shadowing and masking geometry combined using Smith's method
			return Geometry(n, v, k) * Geometry(n, l, k);
		}
	}
	const Elite::RGBColor Fresnel(const Elite::FVector3& h, const Elite::FVector3& v, const Elite::RGBColor& f0)
	{
		//the fresnel function (Schlick)
		const Elite::RGBColor trippleOne{ 1,1,1 }; //Helper variable to do 1 - RGBColor
		const Elite::RGBColor fresnel = f0 + (trippleOne - f0) * std::powf(1 - Elite::Dot(h, v), 5);
		return fresnel;
	}



	const Elite::RGBColor BRDF::Lambert(float reflectance, const Elite::RGBColor& color)
	{
		return (color * reflectance) / float(E_PI);
	}

	const Elite::RGBColor BRDF::Lambert(const Elite::RGBColor& reflectance, const Elite::RGBColor& color)
	{
		return (color * reflectance) / float(E_PI);
	}

	const Elite::RGBColor BRDF::Phong(float specularReflectance, float phongExponent,
		const Elite::FVector3& lightDir, const Elite::FVector3& viewDir, const Elite::FVector3& normal)
	{
		const Elite::FVector3 reflect = lightDir - (2 * Elite::Dot(normal, lightDir)) * normal;
		const float cosAlpha = Elite::Dot(reflect, viewDir);
		float phongValue = specularReflectance * pow(cosAlpha, phongExponent);
		return Elite::RGBColor(phongValue, phongValue, phongValue);
	}

	const Elite::RGBColor BRDF::CookTorrance(const Elite::RGBColor f0, float roughness, bool metalness,
		const Elite::FVector3& lightDir, const Elite::FVector3& viewDir, const Elite::FVector3& normal, const Elite::FVector3& halfVect)
	{
		const float roughnessSqrd = roughness * roughness;

		//Calculation functions
		const float d = NormalDistribution(roughnessSqrd, normal, halfVect);
		const Elite::RGBColor f = Fresnel(halfVect, viewDir, f0);

		//variable k, the remapped roughness for geometry function
		const float k = ((roughnessSqrd + 1) * (roughnessSqrd + 1)) / 8;	//this is for direct lighting, use roughnessSqrd²/2 for inderect lighting

		const float g = GeometrySmith(normal, viewDir, lightDir, k);

		const Elite::RGBColor cookTorrance = (f * d * g) / (4 * Elite::Dot(viewDir, normal) * Elite::Dot(lightDir, normal));

		return cookTorrance;
	}
	
}
