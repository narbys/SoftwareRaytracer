#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const Elite::FMatrix4& translation, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, Material* pMat, Cullmode cullmode)
	: Object({}, pMat)
	, m_TransMat{ translation }
	, m_VertexBuffer{ vertexBuffer }
	, m_IndexBuffer{ indexBuffer }
	, m_Cullmode{cullmode}
{
	Init();
}

TriangleMesh::TriangleMesh(const Elite::FMatrix4& translation, std::vector<Elite::FPoint3>&& vertexBuffer, std::vector<int>&& indexBuffer, Material* pMat, Cullmode cullmode)
	: Object({}, pMat)
	, m_TransMat{ translation }
	, m_VertexBuffer{ std::move(vertexBuffer) }
	, m_IndexBuffer{ std::move(indexBuffer) }
	, m_Cullmode{ cullmode }
{
	Init();
}

TriangleMesh::TriangleMesh(const Elite::FPoint3& pos, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, Material* pMat, Cullmode cullmode)
	: Object({}, pMat)
	, m_VertexBuffer{ vertexBuffer }
	, m_IndexBuffer{ indexBuffer }
	, m_Cullmode{ cullmode }
{
	m_TransMat.Identity();
	for (const Elite::FPoint3& p : vertexBuffer)
	{
		m_Origin.x += p.x;
		m_Origin.y += p.y;
		m_Origin.z += p.z;
	}
	const int vbuffsize = int(vertexBuffer.size());
	m_Origin.x /= vbuffsize;
	m_Origin.y /= vbuffsize;
	m_Origin.z /= vbuffsize;

	m_TransMat = Elite::MakeTranslation(pos - m_Origin);
	Init();
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord, bool shading) const
{
	bool hit{false};
	for (size_t i = 0; i < m_IndexBuffer.size(); i += 3)
	{
		const Elite::FPoint3 v0 = m_VertexBuffer[m_IndexBuffer[i]];
		const Elite::FPoint3 v1 = m_VertexBuffer[m_IndexBuffer[i + size_t(1)]];
		const Elite::FPoint3 v2 = m_VertexBuffer[m_IndexBuffer[i + size_t(2)]];

		HitRecord temphr{};
		const Triangle t{ m_TransMat, v0,v1,v2,m_Cullmode,m_pMaterial };
		if (t.Hit(ray, temphr, shading))
		{
			hit = true;
			if (temphr.tValue < hitRecord.tValue)
			{
				hitRecord = temphr;
			}
		}
	}
	return hit;
}

void TriangleMesh::Init()
{
	UpdateTranslation();
}

void TriangleMesh::UpdateTranslation()
{
	const int bufferSize = int(m_VertexBuffer.size());
	m_TransVertexBuffer.resize(m_VertexBuffer.size());
	for (int i{}; i < bufferSize; i++)
	{
		m_TransVertexBuffer[i] = (m_TransMat * Elite::FPoint4(m_VertexBuffer[i])).xyz;
	}
}
