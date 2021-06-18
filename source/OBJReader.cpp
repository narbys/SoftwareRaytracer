#include "OBJReader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
TriangleMesh* OBJReader::ParseObj(const Elite::FVector3& transVec, const std::string& filepath, Material* pMat, Cullmode cull)
{
	std::ifstream in{ filepath };
	if (!in.good())
		return nullptr;
	std::vector<Elite::FPoint3> vertexBuffer;
	vertexBuffer.reserve(300);
	std::vector<int> indexBuffer;
	indexBuffer.reserve(300);
	std::string str;
	while (std::getline(in, str))
	{
		std::stringstream strstrem{ str };
		char c{};
		strstrem >> c;
		switch (c)
		{
		case 'v':
			float af, bf, cf;
			strstrem >> af;
			strstrem >> bf;
			strstrem >> cf;
			vertexBuffer.emplace_back(af, bf, cf);
			break;
		case 'f':
			int a, b, c;
			strstrem >> a;
			strstrem >> b;
			strstrem >> c;
			a--;
			b--;
			c--;
			indexBuffer.push_back(a);
			indexBuffer.push_back(b);
			indexBuffer.push_back(c);
			break;
		default:
			break;
		}
	}
	return new TriangleMesh{Elite::MakeTranslation(transVec), std::move(vertexBuffer), std::move(indexBuffer), pMat, cull };
}

TriangleMesh* OBJReader::ParseObj(const Elite::FPoint3& transPos, const std::string& filepath, Material* pMat, Cullmode cull)
{
	std::ifstream in{ filepath };
	if (!in.good())
		return nullptr;
	std::vector<Elite::FPoint3> vertexBuffer;
	vertexBuffer.reserve(300);
	std::vector<int> indexBuffer;
	indexBuffer.reserve(300);
	std::string str;
	while (std::getline(in, str))
	{
		std::stringstream strstrem{ str };
		char c{};
		strstrem >> c;
		switch (c)
		{
		case 'v':
			float af, bf, cf;
			strstrem >> af;
			strstrem >> bf;
			strstrem >> cf;
			vertexBuffer.emplace_back(af, bf, cf);
			break;
		case 'f':
			int a, b, c;
			strstrem >> a;
			strstrem >> b;
			strstrem >> c;
			a--;
			b--;
			c--;
			indexBuffer.push_back(a);
			indexBuffer.push_back(b);
			indexBuffer.push_back(c);
			break;
		default:
			break;
		}
	}
	return new TriangleMesh{ transPos, std::move(vertexBuffer), std::move(indexBuffer), pMat, cull };
}
