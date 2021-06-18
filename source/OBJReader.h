#pragma once
#include "EMath.h"
#include <iostream>
#include "TriangleMesh.h"
class TriangleMesh;
class Material;
class OBJReader
{
public:
	OBJReader()=default;
	~OBJReader()=default;
	static TriangleMesh* ParseObj(const Elite::FVector3& transVec, const std::string& filepath, Material* pMat, Cullmode cull);
	static TriangleMesh* ParseObj(const Elite::FPoint3& transPos, const std::string& filepath, Material* pMat, Cullmode cull);
private:
	
};