#pragma once
#include "EMath.h"
#include "ERGBColor.h"
struct HitRecord
{
	Elite::FPoint3 hitPoint{};
	float tValue{FLT_MAX};		//Distance from Oray to p, init to max for only displaying closest
	Elite::FVector3 normal{};
};