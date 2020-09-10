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
	SAFE_RELEASE(Sphere);
}

void CCollider::OnCollision(CGameObject * _pObject)
{
}

void CCollider::Init(float _fRadius)
{
	m_fRadius = _fRadius;
	D3DXCreateSphere(g_Device, m_fRadius, 32, 32, &Sphere, NULL);

}
