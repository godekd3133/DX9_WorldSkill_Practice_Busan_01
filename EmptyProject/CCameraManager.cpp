#include "DXUT.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	m_vPos = Vector3(0, 0, 0);
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
	if (m_fCameraTime > 0.f)
	{
		m_fCameraTime -= dt;
		ShakeCamera();
	}
	m_vShakePos = Lerp(m_vShakePos, m_vPos, dt * 8);

	D3DXMatrixLookAtLH(&m_matView, &(m_vPos + m_vShakePos), &(m_vLookAt + m_vShakePos), &m_vUp);
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

