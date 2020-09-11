 #include "DXUT.h"
#include "CPlayerMovement.h"

CPlayerMovement::CPlayerMovement()
{
}


CPlayerMovement::~CPlayerMovement()
{
}

void CPlayerMovement::Awake()
{
	tf->m_vScale = Vector3(0.01f, 0.01f, 0.01f);
	tf->m_vPos = Vector3(0, 0, 0);
	CAMERA.Follow(go,5.5f);

	ac<CMeshRenderer>()->Init(MESH("PLAYER_RIFLE_IDLE (1)"));
}

void CPlayerMovement::Start()
{

}

void CPlayerMovement::Update()
{
	bool bMove = false;

	Vector3 MoveDirection = this->GetPlayerMoveDirectionFromInput();
	
	m_bFixPlayerRotation = INPUT.KeyPress(VK_CONTROL);

	if (INPUT.KeyDown(VK_LBUTTON))
		this->FirePlayerBullet();
	
	if(MoveDirection != Vector3(0,0,0))
		Move(MoveDirection, GAME.MoveSpeed,                                                                                                                                                                                                                                                                                                                                                                                                                         !m_bFixPlayerRotation);
	else
	{
		if(m_bFixPlayerRotation == false)
			tf->LerpRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0), dt * 16);
	}

	if (INPUT.KeyDown(VK_LSHIFT))
	{
		m_fDashTime = 0.6f;
		m_vVelocity = my::GetDirectionFromQuaternion(tf->m_quatRotation) * 100;
	}
	if (m_fDashTime > 0.f)
	{
		Move(m_vVelocity,1, FALSE);
		m_fDashTime -= dt;
		m_fTime += dt;
		m_vVelocity *= 0.65F;
		
		if (m_fTime > 0.05f)
		{
			m_fTime = 0.f;
			CGameObject * pTrail = OBJ.Create();
			pTrail->tf->m_vPos = tf->m_vPos;
			pTrail->tf->m_vScale = tf->m_vScale;
			pTrail->tf->m_quatRotation = tf->m_quatRotation;
			pTrail->ac<CMeshRenderer>()->Init(gc<CMeshRenderer>()->m_pMesh);
			pTrail->gc<CMeshRenderer>()->sa->Add(
				[=]()->bool {
				return pTrail->gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 0.f), dt * 2);
			});

			pTrail->gc<CMeshRenderer>()->sa->Add(
				[=]()->bool {pTrail->Destroy(); return false; } 
			);

		}
	}
	else m_vVelocity = Vector3(0, 0, 0);

}

void CPlayerMovement::LateUpdate()
{
}

void CPlayerMovement::OnDestroy()
{

}

void CPlayerMovement::OnCollision(CGameObject * _pObject)
{
}

void CPlayerMovement::Move(Vector3 _vDirection, float _MoveSpeed, bool _WithRotation)
{
	Vector3 OldPos = tf->m_vPos;

	if (_WithRotation == true)
		tf->LerpRotation(Vector3(0, my::GetDirAngle(_vDirection), 0), dt * 16);

	tf->m_vPos.x += _vDirection.x * dt * _MoveSpeed;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		tf->m_vPos.x = OldPos.x;
	}

	tf->m_vPos.z += _vDirection.z * dt * _MoveSpeed;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		tf->m_vPos.z = OldPos.z;
	}
}

Vector3 CPlayerMovement::GetPlayerMoveDirectionFromInput()
{
	Vector3 MoveDirection = Vector3(0, 0, 0);

	if (INPUT.KeyPress('D'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Right];
	else if (INPUT.KeyPress('A'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Left];
	if (INPUT.KeyPress('W'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Foward];
	else if (INPUT.KeyPress('S'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Back];

	return MoveDirection;
}

void CPlayerMovement::FirePlayerBullet()
{
	Vector3 bulletPosition = tf->m_vPos;
	Vector3 bulletOffset = Vector3(-0.4f, 1.4f, 1.f);
	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &tf->m_quatRotation);
	D3DXVec3TransformCoord(&bulletOffset, &bulletOffset, &matRot);

	CGameObject * Bullet = OBJ.Create();
	Bullet->ac<CPlayerBullet>()->Init(bulletPosition + bulletOffset, my::GetDirectionFromQuaternion(tf->m_quatRotation), 100);
}

