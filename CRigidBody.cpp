#include "DXUT.h"
#include "CRigidBody.h"


CRigidBody::CRigidBody()
{
	m_vVelocity = Vector3(0, 0, 0);
}


CRigidBody::~CRigidBody()
{
}

void CRigidBody::Awake()
{
}

void CRigidBody::Start()
{
}

void CRigidBody::Update()
{
}

void CRigidBody::LateUpdate()
{
	if (tf->m_vPos.y > 0)
		m_vVelocity.y -= 3000.f * dt;

	m_vVelocity.x *= 0.94f;
	m_vVelocity.y *= 0.98f;

	tf->m_vPos += m_vVelocity * dt;
	
	if (m_vVelocity.y < 0.f)
	{
		if (tf->m_vPos.y < 0)
		{
			for (auto iter : OnLanding)
			{
				iter();
			}
			m_vVelocity.y = 0.f;
			m_vVelocity.x = 0.f;
			tf->m_vPos.y = 0.f;

		}
	}

}

void CRigidBody::OnDestroy()
{
}

void CRigidBody::OnCollision()
{
}

void CRigidBody::AddForce(Vector3 _vVelocitiy)
{
	m_vVelocity += _vVelocitiy;
}
