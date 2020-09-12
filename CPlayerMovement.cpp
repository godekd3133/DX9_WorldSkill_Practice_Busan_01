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
	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("PISTOL_IDLE", "PLAYER_PISTOL_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_RUN", "PLAYER_PISTOL_RUN", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_DASH", "PLAYER_PISTOL_RUN", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("PISTOL_WALK", "PLAYER_PISTOL_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_SHOOT", "PLAYER_PISTOL_SHOOT", 10.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("PISTOL_SKILL", "PLAYER_PISTOL_SKILL", 30.f / 1000.f, false);

	gc<CAnimator3D>()->AddState("RIFLE_IDLE", "PLAYER_RIFLE_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_RUN", "PLAYER_RIFLE_RUN", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_DASH", "PLAYER_RIFLE_RUN", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("RIFLE_WALK", "PLAYER_RIFLE_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_SHOOT", "PLAYER_RIFLE_SHOOT", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("RIFLE_SKILL", "PLAYER_RIFLE_SKILL", 30.f / 1000.f, false);

	gc<CAnimator3D>()->GetState("PISTOL_SHOOT")->AddEvent(4, [=]() { this->FirePlayerBullet(); });

	Animation_SetState("PISTOL_IDLE");
}

void CPlayerMovement::Start()
{

}

void CPlayerMovement::Update()
{
	bool bMove = false;
	bool bRun = false;
	bool bDash = false;
	bool bShoot = false;

	Vector3 MoveDirection = this->GetPlayerMoveDirectionFromInput();
	
	if (MoveDirection != Vector3(0, 0, 0))
		bMove = true;
	GAME.m_fFireTime[m_iWeaponMode] += dt;

	if (INPUT.KeyDown(VK_LBUTTON) && GAME.m_fFireTime[m_iWeaponMode] > GAME.m_fFireDelay[m_iWeaponMode])
	{
		bShoot = true;
	}

if(MoveDirection.z == 1 || bMove== false && m_bFixPlayerRotation == false)
	tf->LerpRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0), dt * 16);

	m_bFixPlayerRotation = INPUT.KeyPress(VK_CONTROL);

	if (INPUT.KeyPress(VK_LSHIFT))
		bRun = true;
	if (INPUT.KeyDown(VK_SPACE))
		bDash = true;

	if (Animation_GetCurrentStateName == GetAnimationStateByWeapon() + "IDLE")
	{
		if (bMove == true)
			Animation_SetState(GetAnimationStateByWeapon() + "WALK");
		if (bShoot == true)
		{
			GAME.m_fFireTime[m_iWeaponMode] = 0.f;
			Animation_SetState(GetAnimationStateByWeapon() + "SHOOT");
		}
	}
	else if (Animation_GetCurrentStateName == GetAnimationStateByWeapon() + "WALK")
	{
		Move(MoveDirection, GAME.MoveSpeed, !m_bFixPlayerRotation);
		
		if (bMove == false)
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
		if(bRun == true)
			Animation_SetState(GetAnimationStateByWeapon() + "RUN");
		if (bShoot == true)
		{
			GAME.m_fFireTime[m_iWeaponMode] = 0.f;
			Animation_SetState(GetAnimationStateByWeapon() + "SHOOT");
		}
		if (bDash == true && bMove == true)
		{
			tf->SetRotation(Vector3(0, my::GetDirAngle(MoveDirection), 0));
			m_fDashTime = 0.2f;
			m_vVelocity = my::GetDirectionFromQuaternion(tf->m_quatRotation) * 100;
			Animation_SetState(GetAnimationStateByWeapon() + "DASH");
		}
		
	}
	else if (Animation_GetCurrentStateName == GetAnimationStateByWeapon() + "RUN")
	{
		Move(MoveDirection, GAME.MoveSpeed * 1.75f, !m_bFixPlayerRotation);
		if (bDash == true && bMove == true)
		{
			tf->SetRotation(Vector3(0, my::GetDirAngle(MoveDirection), 0));
			m_fDashTime = 0.2f;
			m_vVelocity = my::GetDirectionFromQuaternion(tf->m_quatRotation) * 100;
			Animation_SetState(GetAnimationStateByWeapon() + "DASH");
		}

		if (bMove == false)
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
	
		else if (bRun == false)
		{
				Animation_SetState(GetAnimationStateByWeapon() + "WALK");
		}
	}
	else if (Animation_GetCurrentStateName == GetAnimationStateByWeapon() + "DASH")
	{
		if (m_fDashTime > 0.f)
		{
			gc<CAnimator3D>()->GetCurrentState()->m_bEnable = false;
			Move(m_vVelocity, 1, FALSE);
			m_fDashTime -= dt;
			m_fTime += dt;
			m_vVelocity *= 0.65F;

			if (m_fTime > 0.025f)
			{
				m_fTime = 0.f;
				CGameObject * pTrail = OBJ.Create();
				pTrail->tf->m_vPos = tf->m_vPos;
				pTrail->tf->m_vScale = tf->m_vScale;
				pTrail->tf->m_quatRotation = tf->m_quatRotation;
				pTrail->ac<CMeshRenderer>()->Init(gc<CMeshRenderer>()->m_pMesh);
				pTrail->gc<CMeshRenderer>()->sa->Add(
					[=]()->bool {
					return pTrail->gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 0.f), dt / 2);
				});

				pTrail->gc<CMeshRenderer>()->sa->Add(
					[=]()->bool {pTrail->Destroy(); return false; }
				);

			}
		}		
		else
		{
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
		}
	}

	else if (Animation_GetCurrentStateName == GetAnimationStateByWeapon() + "SHOOT")
	{
		if (Animation_GetNormalizeTime >= 0.99f)
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
		if (bDash == true && bMove == true)
		{
			tf->SetRotation(Vector3(0, my::GetDirAngle(MoveDirection), 0));
			m_fDashTime = 0.2f;
			m_vVelocity = my::GetDirectionFromQuaternion(tf->m_quatRotation) * 100;
			Animation_SetState(GetAnimationStateByWeapon() + "DASH");
		}
		else if (bShoot == true)
		{
			GAME.m_fFireTime[m_iWeaponMode] = 0.f;
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
			Animation_SetState(GetAnimationStateByWeapon() + "SHOOT");
		}
		
	}


	

	if (INPUT.KeyDown('1'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CEnemy01>()->Init(Vector3(-5,0,5 ));
	}

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

string CPlayerMovement::GetAnimationStateByWeapon()
{
	if (m_iWeaponMode == 0)
		return "PISTOL_";
	else if (m_iWeaponMode == 1)
		return "RIFLE_";
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
	if(m_bFixPlayerRotation == false)
	tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0));
	
	Vector3 bulletPosition = tf->m_vPos;
	Vector3 bulletOffset = Vector3(-0.4f, 1.4f, 0.2f);
	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &tf->m_quatRotation);
	D3DXVec3TransformCoord(&bulletOffset, &bulletOffset, &matRot);

	CGameObject * Bullet = OBJ.Create();
	Bullet->ac<CPlayerBullet>()->Init(bulletPosition + bulletOffset, my::GetDirectionFromQuaternion(tf->m_quatRotation), 100);
}

