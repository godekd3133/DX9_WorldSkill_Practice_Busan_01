#include "DXUT.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	m_vPos = Vector3(0, 5, -50);
	m_vLookAt = Vector3(0, 0, 0);
	m_vUp = Vector3(0, 1, 0);
	sa = new CScheduleAdmin();

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLookAt, &m_vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 1000000);

	m_vShakePos = m_vPos;
	m_fCameraTime = 0.f;
	m_fShakePower = 0.f;
}

CCameraManager::~CCameraManager()
{
	SAFE_DELETE(sa);
}

void CCameraManager::Update()
{
	Vector3 Offset = m_vOffset;
	if (m_fCameraTime > 0.f)
	{
		m_fCameraTime -= dt;
		ShakeCamera();
	}
	m_vShakePos = Lerp(m_vShakePos, Vector3(0,0,0), dt * 8);

	if (m_pFollowObject)
	{
		m_vLookAt = m_pFollowObject->tf->m_vPos + Vector3(0, 2, 0);
		Vector2 dtPos = INPUT.GetDeltaMousePos();
		
		m_vRotation.y += dtPos.x * dt * m_fSensitivity;
		m_vRotation.x += dtPos.y * dt * m_fSensitivity;

		Matrix matRot, matRotX, matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_vRotation.y));
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_vRotation.x));
		D3DXVec3TransformNormal(&m_vFoward, &Vector3(0,0,1), &(matRotX* matRotY));
		
		D3DXVec3TransformNormal(&Offset, &m_vOffset, &(matRotY));

		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Foward], &Vector3(0, 0, 1), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Back], &Vector3(0, 0, -1), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Right], &Vector3(1, 0, 0), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Left], &Vector3(-1, 0, 0), &(matRotY));

		m_vPos = m_vLookAt - m_vFoward * m_fDistance;

		//m_vLookAt.x = Lerp(m_vLookAt.x, m_pFollowObject->tf->m_vPos.x, dt * 2);
		//m_vPos = m_vLookAt + Vector3(0,80,-400);
	}

	D3DXMatrixLookAtLH(&m_matView, &(m_vPos + m_vShakePos + Offset), &(m_vLookAt + m_vShakePos + Offset), &m_vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 1000000);
}

void CCameraManager::SetTransform()
{
	g_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	g_Device->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCameraManager::Shake(float _fTime, float _fPower)
{
	m_fShakePower = _fPower;
	m_fCameraTime = _fTime;
}

