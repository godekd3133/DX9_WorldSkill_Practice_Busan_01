#include "DXUT.h"
#include "CCollider.h"


CCollider::CCollider()
{
	OBJ.m_listCollider3D.push_back(this);
}


CCollider::~CCollider()
{
	OBJ.m_listCollider3D.remove(this);
}

void CCollider::Awake()
{
}

void CCollider::Start()
{
}

void CCollider::Update()
{
}

void CCollider::LateUpdate()
{
}

void CCollider::OnDestroy()
{
}

void CCollider::OnCollision()
{
}

void CCollider::Init(float _fRadius)
{
	m_fRadius = m_fRadius;
}
