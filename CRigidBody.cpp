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
	m_pMap = GAME.m_pMap;
}

void CRigidBody::Update()
{
}

void CRigidBody::LateUpdate()
{
	Vector3 vMovePos = tf->m_vPos + m_vVelocity * dt;

	m_vVelocity.x -= m_vVelocity.x * m_vImpulse.x  * dt;
	m_vVelocity.y -= m_vVelocity.y * 0.035f * dt;
	m_vVelocity.z -= m_vVelocity.z * m_vImpulse.z * dt;

	tf->m_vPos.y = vMovePos.y;
	tf->m_vPos.x = vMovePos.x;
	tf->m_vPos.z = vMovePos.z;
}

void CRigidBody::OnDestroy()
{
}

void CRigidBody::OnCollision(CGameObject * _pObject)
{
}

void CRigidBody::AddForce(Vector3 _vVelocitiy, Vector3 _vImpulse)
{
	m_vVelocity += _vVelocitiy;
	m_vImpulse = _vImpulse;
}
