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
	
	ac<CCollider>()->Init(0.7f);


	ac<CMeshRenderer>()->Init(MESH("PLAYER_RIFLE_IDLE (1)"));
	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("PISTOL_IDLE", "PLAYER_PISTOL_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_RUN", "PLAYER_PISTOL_RUN", 20.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_DASH", "PLAYER_PISTOL_RUN", 20.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("PISTOL_WALK", "PLAYER_PISTOL_WALK", 20.f / 1000.f);
	gc<CAnimator3D>()->AddState("PISTOL_SHOOT", "PLAYER_PISTOL_SHOOT", 10.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("PISTOL_SKILL", "PLAYER_PISTOL_SKILL", 30.f / 1000.f, false);

	gc<CAnimator3D>()->AddState("RIFLE_IDLE", "PLAYER_RIFLE_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_RUN", "PLAYER_RIFLE_RUN", 20.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_DASH", "PLAYER_RIFLE_RUN", 20.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("RIFLE_WALK", "PLAYER_RIFLE_WALK", 20.f / 1000.f);
	gc<CAnimator3D>()->AddState("RIFLE_SHOOT", "PLAYER_RIFLE_SHOOT", 10.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("RIFLE_SKILL", "PLAYER_RIFLE_SKILL", 30.f / 1000.f, false);

	gc<CAnimator3D>()->GetState("PISTOL_SHOOT")->AddEvent(4, [=]() { this->FirePlayerBullet(); });
	gc<CAnimator3D>()->GetState("RIFLE_SHOOT")->AddEvent(4, [=]() { this->FirePlayerBullet(); });

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

	if (m_bReload == true)
	{
		m_fReloadTime += dt;
		if (m_fReloadTime > m_fReloadDelay)
		{
			Reload();
			m_fReloadTime = 0.f;
			m_bReload = false;
		}
	}
	else
	{
		if (m_iWeaponMode == 0)
		{
			if (INPUT.KeyDown(VK_LBUTTON) && CanFireBullet())
				bShoot = true;
		}
		else
		{
			if (INPUT.KeyPress(VK_LBUTTON) && CanFireBullet())
				bShoot = true;
			else if (GAME.m_iCurrentBullet[m_iWeaponMode] == 0)
				m_bReload = true;
		}
	}


if(MoveDirection.z == 1 || bMove== false && m_bFixPlayerRotation == false)
	tf->LerpRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0), dt * 16);

	m_bFixPlayerRotation = INPUT.KeyPress(VK_CONTROL);

	if (INPUT.KeyPress(VK_LSHIFT))
		bRun = true;
	if (INPUT.KeyDown(VK_SPACE))
		bDash = true;
	if (INPUT.KeyDown('R') && CanReload())
		m_bReload = true;

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
			m_fDashTime = 0.3f;
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
			m_fDashTime = 0.3f;
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
			m_vVelocity -= m_vVelocity * 20.f * dt;

			if (m_fTime > 0.025f)
			{
				m_fTime = 0.f;
				CGameObject * pTrail = OBJ.Create();

				pTrail->tf->m_vPos = tf->m_vPos;
				pTrail->tf->m_vScale = tf->m_vScale;
				pTrail->tf->m_quatRotation = tf->m_quatRotation;

				pTrail->ac<CMeshRenderer>()->Init(gc<CMeshRenderer>()->m_pMesh);
				pTrail->gc<CMeshRenderer>()->sa->Add(			[=]()->bool {
					return pTrail->gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 0.f), dt * 10);			});

				pTrail->gc<CMeshRenderer>()->sa->Add(			[=]()->bool {
					pTrail->Destroy(); return false; }
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
		else if (bShoot == true )
		{
			GAME.m_fFireTime[m_iWeaponMode] = 0.f;
			Animation_SetState(GetAnimationStateByWeapon() + "IDLE");
			Animation_SetState(GetAnimationStateByWeapon() + "SHOOT");
		}
		
	}


	if (INPUT.KeyDown('1'))
	{
		m_iWeaponMode = 0;

		Animation_SetState(GetAnimationStateByWeapon() + Animation_GetCurrentStateName.substr(Animation_GetCurrentStateName.find("_")+1));
	}
	else if (INPUT.KeyDown('2'))
	{
		m_iWeaponMode = 1;
		Animation_SetState(GetAnimationStateByWeapon() + Animation_GetCurrentStateName.substr(Animation_GetCurrentStateName.find("_")+1));
	}

	if (INPUT.KeyDown('3'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CEnemy01>()->Init(Vector3(-5,0,5 ));
	}
	if (INPUT.KeyDown('4'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CEnemy02>()->Init(Vector3(-5, 0, 5));
	}
	if (INPUT.KeyDown('5'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CEnemy03>()->Init(Vector3(-5, 0, 5));
	}
	if (INPUT.KeyDown('6'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CBoss01>()->Init(Vector3(-5, 0, 5));
	}

	if (INPUT.KeyDown('7'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CBoss02>()->Init(Vector3(-5, 0, 5));
	}
	if (INPUT.KeyDown('8'))
	{
		Vector3  Axis[4];
		Axis[0] = my::GetRotatedDir(Vector3(0, 0, 1), 45);
		Axis[1] = my::GetRotatedDir(Vector3(0, 0, 1), 90 + 45);
		Axis[2] = my::GetRotatedDir(Vector3(0, 0, 1), 180 + 45);
		Axis[3] = my::GetRotatedDir(Vector3(0, 0, 1), 270 + 45);
		sa->Add(
			[=]()->bool {
			CAMERA.Shake(0.05f, 1.f);
			EFFECT2(tf->m_vPos + Axis[0] * 1 ,  Vector3(0.005, 0.005, 0.005), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[1] * 1 , Vector3(0.005, 0.005, 0.005), "EFFECT_PLAYER_SKILL_02" );
			EFFECT2(tf->m_vPos + Axis[2] * 1 , Vector3(0.005, 0.005, 0.005), "EFFECT_PLAYER_SKILL_02" );
			EFFECT2(tf->m_vPos + Axis[3] * 1 , Vector3(0.005, 0.005, 0.005), "EFFECT_PLAYER_SKILL_02" );
			return false;
		});

		sa->Delay(0.3f);

		sa->Add(
			[=]()->bool {
			CAMERA.Shake(0.05f, 1.25f);
			EFFECT2(tf->m_vPos + Axis[0] * 3 , Vector3(0.0075, 0.0075, 0.0075), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[1] * 3 , Vector3(0.0075, 0.0075, 0.0075), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[2] * 3 , Vector3(0.0075, 0.0075, 0.0075), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[3] * 3 , Vector3(0.0075, 0.0075, 0.0075), "EFFECT_PLAYER_SKILL_02");
			return false;
		});

		sa->Delay(0.4f);

		sa->Add(
			[=]()->bool {
			CAMERA.Shake(0.15f, 1.75f);
			EFFECT2(tf->m_vPos + Axis[0] * 5 , Vector3(0.01, 0.01, 0.01), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[1] * 5 , Vector3(0.01, 0.01, 0.01), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[2] * 5 , Vector3(0.01, 0.01, 0.01), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[3] * 5 , Vector3(0.01, 0.01, 0.01), "EFFECT_PLAYER_SKILL_02");
			return false;
		});

		sa->Delay(0.5f);

		sa->Add(
			[=]()->bool {
			CAMERA.Shake(0.25f, 2.5f);
			EFFECT2(tf->m_vPos + Axis[0] * 7, Vector3(0.0125, 0.0125, 0.0125), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[1] * 7, Vector3(0.0125, 0.0125, 0.0125), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[2] * 7, Vector3(0.0125, 0.0125, 0.0125), "EFFECT_PLAYER_SKILL_02");
			EFFECT2(tf->m_vPos + Axis[3] * 7, Vector3(0.0125, 0.0125, 0.0125), "EFFECT_PLAYER_SKILL_02");
			return false;
		});
	}

	if (INPUT.KeyDown('Z'))
	{
		CGameObject * Enemy = OBJ.Create();
		Enemy->ac<CObstacle>()->Init(ObstacleType::Thom,tf->m_vPos);
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
	GAME.m_iCurrentBullet[m_iWeaponMode]--;
	if(m_bFixPlayerRotation == false)
	tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0));
	
	Vector3 bulletPosition = tf->m_vPos;
	Vector3 bulletOffset = Vector3(-0.25f, 1.4f, 1.f);
	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &tf->m_quatRotation);
	D3DXVec3TransformCoord(&bulletOffset, &bulletOffset, &matRot);

	
	CGameObject * Bullet = OBJ.Create();
	Bullet->ac<CPlayerBullet>()->Init(bulletPosition + bulletOffset, my::GetDirectionFromQuaternion(tf->m_quatRotation), 100, GAME.m_iBulletDamage[m_iWeaponMode]);

	if (m_iWeaponMode == 1)
		Bullet->gc<CMeshRenderer>()->m_pMappingOverride = SPRITE("BULLET_MAPPING_02");
}

bool CPlayerMovement::CanFireBullet()
{
	return GAME.m_iCurrentBullet[m_iWeaponMode] > 0 && GAME.m_fFireTime[m_iWeaponMode] > GAME.m_fFireDelay[m_iWeaponMode];
}

bool CPlayerMovement::CanReload()
{
	if (m_bReload)
		return false;

	if (m_iWeaponMode == 0)
		return GAME.m_iCurrentBullet[m_iWeaponMode] != GAME.m_iMaxBullet[m_iWeaponMode];

	return GAME.m_iHavingBullet[m_iWeaponMode] > 0 ;
}

void CPlayerMovement::Reload()
{
	if (m_iWeaponMode == 0)
		GAME.m_iCurrentBullet[m_iWeaponMode] = GAME.m_iMaxBullet[m_iWeaponMode];
	else
	{
		GAME.m_iHavingBullet[m_iWeaponMode] -=  (GAME.m_iMaxBullet[m_iWeaponMode] - GAME.m_iCurrentBullet[m_iWeaponMode]);
		GAME.m_iCurrentBullet[m_iWeaponMode] += (GAME.m_iMaxBullet[m_iWeaponMode] - GAME.m_iCurrentBullet[m_iWeaponMode]);
	}
	
		
}

