#include "DXUT.h"
#include "CTransform.h"


CTransform::CTransform()
{
}


CTransform::~CTransform()
{
}

void CTransform::Awake()
{
}

void CTransform::Start()
{
}

void CTransform::Update()
{
}

void CTransform::LateUpdate()
{
}

void CTransform::OnDestroy()
{
}

void CTransform::OnCollision()
{
}

Vector3 CTransform::GetRotation()
{
	Vector3 vRot;

	D3DXQuaternionToAxisAngle(&m_quatRotation, &Vector3(1, 0, 0), &vRot.x);
	D3DXQuaternionToAxisAngle(&m_quatRotation, &Vector3(0, 1, 0), &vRot.y);
	D3DXQuaternionToAxisAngle(&m_quatRotation, &Vector3(0, 0, 1), &vRot.z);

	vRot.x = D3DXToDegree(vRot.x);
	vRot.y = D3DXToDegree(vRot.y);
	vRot.z = D3DXToDegree(vRot.z);

	return vRot;
}

void CTransform::SetRotation(Vector3 _vRot)
{
	m_quatRotation = my::QuatEular(_vRot);
}

bool CTransform::LerpRotation(Vector3 _vTarget, float _fTime)
{
	D3DXQuaternionSlerp(&m_quatRotation, &m_quatRotation, &QuatEular(_vTarget), _fTime);

	float dist = my::GetLength(GetRotation(), _vTarget);
	
	if (dist < 3.f)
	{
		return false;
	}
	return true;
}

bool CTransform::MoveToward(Vector3 _vTarget, float _fDist)
{
	Vector3 vDir = my::GetDirection(m_vPos, _vTarget);
	m_vPos += vDir * _fDist;


	if (my::GetLength(_vTarget, m_vPos) < 10.f)
	{
		return false;
	}
	return true;
}

bool CTransform::LerpPosition(Vector3 _vTarget, float _fTime)
{
	m_vPos = Lerp(m_vPos, _vTarget, _fTime);

	if (my::GetLength(m_vPos, _vTarget) < 10.f)
		return false;

	return true;
}

bool CTransform::LerpScale(Vector3 _vTarget, float _fTime)
{
	m_vScale = Lerp(m_vScale, _vTarget, _fTime);

	if (my::GetLength(m_vScale, _vTarget) < 0.1f)
		return false;

	return true;
}

Matrix CTransform::ToMatrix()
{
	Matrix matTrans, matRot, matScale, matWorld;

	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationQuaternion(&matRot, &m_quatRotation);

	matWorld = matScale * matRot * matTrans;

	if (go->m_pParent)
	{
		matWorld *= go->m_pParent->tf->ToMatrix();
	}

	return matWorld;
}
