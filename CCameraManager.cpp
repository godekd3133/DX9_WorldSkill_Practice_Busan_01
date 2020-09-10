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
	sa->Update();
	Vector3 Offset = m_vOffset;
	if (m_fCameraTime > 0.f)
	{
		m_fCameraTime -= udt;
		ShakeCamera();
	}
	m_vShakePos = Lerp(m_vShakePos, Vector3(0,0,0), udt * 8);

	if (m_pFollowObject)
	{
		if (m_bScrolling)
		{
			m_vLookAt = m_pFollowObject->tf->m_vPos + Vector3(0, 300, 0);
			Vector2 dtPos = INPUT.GetDeltaMousePos();

			m_vRotation.y += dtPos.x * dt * m_fSensitivity;
			m_vRotation.x += dtPos.y * dt * m_fSensitivity;
		}
		Matrix matRot, matRotX, matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_vRotation.y));
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_vRotation.x));
		D3DXVec3TransformNormal(&m_vFoward, &Vector3(0,0,1), &(matRotX* matRotY));
		D3DXVec3TransformCoord(&Offset, &Offset, &(matRotX* matRotY));
		
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Foward], &Vector3(0, 0, 1), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Back], &Vector3(0, 0, -1), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Right], &Vector3(1, 0, 0), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::Left], &Vector3(-1, 0, 0), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::LF], &Vector3(-0.5, 0, 0.5), &(matRotY));
		D3DXVec3TransformNormal(&m_vCharactorAxis[Axis::RF], &Vector3(0.5, 0, 0.5), &(matRotY));

		m_vPos = m_vLookAt - m_vFoward * m_fDistance + Offset;

		//m_vLookAt.x = Lerp(m_vLookAt.x, m_pFollowObject->tf->m_vPos.x, dt * 2);
		//m_vPos = m_vLookAt + Vector3(0,80,-400);
	}

	D3DXMatrixLookAtLH(&m_matView, &(m_vPos + m_vShakePos ), &(m_vLookAt + m_vShakePos ), &m_vUp);
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

bool CCameraManager::RayCast(CMeshRenderer * _pTarget, Vector3 _vPos, Vector3 _vDirection, float _fDistance, CollisionInfo& _Info)
{
	D3DXVECTOR3		vPickRayDir = _vDirection;				// Pick ray direction	
	D3DXVECTOR3		vPickRayOrig = _vPos;				// Pick ray origin
	D3DXVECTOR3					v;				// Vector used in computation	
	D3DXMATRIXA16				matProj;		// Retrieved projection matrix	
	D3DXMATRIXA16				matView, m;		// Retrieved view and computation matrices
	POINT						ptCursor;		// Cursor position	
	D3DXVECTOR3					vNear, vDir;
	D3DXMATRIX					invMat;
	BOOL						bHit;
	DWORD						dwIndex;
	float						uCoord, vCoord;
	float						dist;
	//LPDIRECT3DSURFACE9			pBackBuffer = NULL;
	//D3DSURFACE_DESC				Desc;	// Error check	
	//g_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//pBackBuffer->GetDesc(&Desc);
	//pBackBuffer->Release();	// Get the projection matrix

	D3DXMatrixInverse(&invMat, NULL, &_pTarget->tf->ToMatrix());
	D3DXVec3TransformCoord(&vNear, &vPickRayOrig, &invMat);
	D3DXVec3TransformNormal(&vDir, &vPickRayDir, &invMat);	// Test for intersection	


	D3DXIntersect(_pTarget->m_pMesh->m_pMesh, &vNear, &vDir, &bHit, &dwIndex, &uCoord, &vCoord, &dist, NULL, NULL);
	if (bHit == TRUE)
	{
		if (_fDistance == -1.f)
		{
			_Info.distance = dist;
			_Info.vPos = _vPos + _vDirection * dist;

			return TRUE;
		}
		else
		{
			if (dist <= _fDistance)
			{
				_Info.distance = dist;
				_Info.vPos = _vPos + _vDirection * dist;
				return true;
			}
		}

	}
	return FALSE;
}

bool CCameraManager::RayCastAtBox(Vector3 _Radius, Matrix _matWorld, Vector3 _vPos, Vector3 _vDirection, float _fDistance, CollisionInfo & _Info)
{
	LPD3DXMESH Box;
	
	D3DXCreateBox(g_Device, _Radius.x, _Radius.y, _Radius.z, &Box, NULL);
	
	
	
	
	
	
	D3DXVECTOR3		vPickRayDir = _vDirection;				// Pick ray direction	
	D3DXVECTOR3		vPickRayOrig = _vPos;				// Pick ray origin
	D3DXVECTOR3					v;				// Vector used in computation	
	D3DXMATRIXA16				matProj;		// Retrieved projection matrix	
	D3DXMATRIXA16				matView, m;		// Retrieved view and computation matrices
	POINT						ptCursor;		// Cursor position	
	D3DXVECTOR3					vNear, vDir;
	D3DXMATRIX					invMat;
	BOOL						bHit;
	DWORD						dwIndex;
	float						uCoord, vCoord;
	float						dist;
	//LPDIRECT3DSURFACE9			pBackBuffer = NULL;
	//D3DSURFACE_DESC				Desc;	// Error check	
	//g_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//pBackBuffer->GetDesc(&Desc);
	//pBackBuffer->Release();	// Get the projection matrix
	
	D3DXMatrixInverse(&invMat, NULL, &_matWorld);
	D3DXVec3TransformCoord(&vNear, &vPickRayOrig, &invMat);
	D3DXVec3TransformNormal(&vDir, &vPickRayDir, &invMat);	// Test for intersection	
	
	
	D3DXIntersect(Box, &vNear, &vDir, &bHit, &dwIndex, &uCoord, &vCoord, &dist, NULL, NULL);
	if (bHit == TRUE)
	{
		if (_fDistance == -1.f)
		{
			_Info.distance = dist;
			_Info.vPos = _vPos + _vDirection * dist;
	
			return TRUE;
		}
		else
		{
			if (dist <= _fDistance)
			{
				_Info.distance = dist;
				_Info.vPos = _vPos + _vDirection * dist;
				return true;
			}
		}
	
	}
	return FALSE;
}

bool CCameraManager::RayCastAtSphere(LPD3DXMESH _Sphere, Matrix _matWorld, Vector3 _vPos, Vector3 _vDirection, float _fDistance, CollisionInfo & _Info)
{
	if (_Sphere == NULL)
		return false;
	D3DXVECTOR3		vPickRayDir = _vDirection;				// Pick ray direction	
	D3DXVECTOR3		vPickRayOrig = _vPos;				// Pick ray origin
	D3DXVECTOR3					v;				// Vector used in computation	
	D3DXMATRIXA16				matProj;		// Retrieved projection matrix	
	D3DXMATRIXA16				matView, m;		// Retrieved view and computation matrices
	POINT						ptCursor;		// Cursor position	
	D3DXVECTOR3					vNear, vDir;
	D3DXMATRIX					invMat;
	BOOL						bHit;
	DWORD						dwIndex;
	float						uCoord, vCoord;
	float						dist;
	//LPDIRECT3DSURFACE9			pBackBuffer = NULL;
	//D3DSURFACE_DESC				Desc;	// Error check	
	//g_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//pBackBuffer->GetDesc(&Desc);
	//pBackBuffer->Release();	// Get the projection matrix
	
	D3DXMatrixInverse(&invMat, NULL, &_matWorld);
	D3DXVec3TransformCoord(&vNear, &vPickRayOrig, &invMat);
	D3DXVec3TransformNormal(&vDir, &vPickRayDir, &invMat);	// Test for intersection	
	
	
	D3DXIntersect(_Sphere, &vNear, &vDir, &bHit, &dwIndex, &uCoord, &vCoord, &dist, NULL, NULL);
	if (bHit == TRUE)
	{
		if (_fDistance == -1.f)
		{
			_Info.distance = dist;
			_Info.vPos = _vPos + _vDirection * dist;
	
			return TRUE;
		}
		else
		{
			if (dist <= _fDistance)
			{
				_Info.distance = dist;
				_Info.vPos = _vPos + _vDirection * dist;
				return true;
			}
		}
	
	}
	return FALSE;
}
