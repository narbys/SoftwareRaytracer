#pragma once
#include <vector>
#include "Triangle.h"
class TriangleMesh final: public Object
{
public:
	TriangleMesh(const Elite::FMatrix4& translation, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, Material* pMat,Cullmode cullmode);
	TriangleMesh(const Elite::FMatrix4& translation, std::vector<Elite::FPoint3>&& vertexBuffer, std::vector<int>&& indexBuffer, Material* pMat, Cullmode cullmode);
	TriangleMesh(const Elite::FPoint3& pos, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, Material* pMat, Cullmode cullmode);
	virtual ~TriangleMesh()=default;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shading=false)const override;
private:
	std::vector<Elite::FPoint3> m_VertexBuffer;
	std::vector<Elite::FPoint3> m_TransVertexBuffer;
	const std::vector<int> m_IndexBuffer;
	const Cullmode m_Cullmode;
	Elite::FMatrix4 m_TransMat;
	void Init();
	void UpdateTranslation();
};