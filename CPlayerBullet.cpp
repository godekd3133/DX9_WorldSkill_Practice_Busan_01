#include "DXUT.h"
#include "CPlayerBullet.h"


CPlayerBullet::CPlayerBullet()
{
}


CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Awake()
{
}

void CPlayerBullet::Start()
{
}

void CPlayerBullet::Update()
{
	tf->m_vPos += m_vDirection * m_fSpeed * dt;
	tf->SetRotation(Vector3(0, my::GetDirAngle(m_vDirection), 0));

	m_fTime += dt;
	//if (m_fTime > 0.025f)
	{
		m_fTime = 0.f;
		CGameObject * pTrail = OBJ.Create();

		pTrail->tf->m_vPos = tf->m_vPos;
		pTrail->tf->m_vScale = tf->m_vScale;
		pTrail->tf->m_quatRotation = tf->m_quatRotation;

		pTrail->ac<CMeshRenderer>()->Init(gc<CMeshRenderer>()->m_pMesh);
		pTrail->gc<CMeshRenderer>()->m_pMappingOverride = gc<CMeshRenderer>()->m_pMappingOverride;
		pTrail->gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return pTrail->gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 0.f), dt * 24);			});

		pTrail->gc<CMeshRenderer>()->sa->Add([=]()->bool {
			pTrail->Destroy(); return false; }
		);
	}tf->m_vPos += m_vDirection * m_fSpeed * dt;
	tf->SetRotation(Vector3(0, my::GetDirAngle(m_vDirection), 0));

	m_fTime += dt;
	//if (m_fTime > 0.025f)
	{
		m_fTime = 0.f;
		CGameObject * pTrail = OBJ.Create();

		pTrail->tf->m_vPos = tf->m_vPos;
		pTrail->tf->m_vScale = tf->m_vScale;
		pTrail->tf->m_quatRotation = tf->m_quatRotation;

		pTrail->ac<CMeshRenderer>()->Init(gc<CMeshRenderer>()->m_pMesh);
		pTrail->gc<CMeshRenderer>()->m_pMappingOverride = gc<CMeshRenderer>()->m_pMappingOverride;
		pTrail->gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return pTrail->gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 0.f), dt * 24);			});

		pTrail->gc<CMeshRenderer>()->sa->Add([=]()->bool {
			pTrail->Destroy(); return false; }
		);
	}



	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		EFFECT(tf->m_vPos , Vector3(0.002, 0.002, 0.002), "EFFECT_EXPLOSION");
		go->Destroy();
	}
}

void CPlayerBullet::LateUpdate()
{
}

void CPlayerBullet::OnDestroy()
{
}

void CPlayerBullet::OnCollision(CGameObject * _pObject)
{
	if (go->m_bDestroy == false)
	{

		if (_pObject->m_Tag == Tag::Enemy)
		{
			if (_pObject->gc<CEnemy>()->m_bIsDead == false)
			{
				EFFECT(_pObject->tf->m_vPos + Vector3(RandRange(-10, 10) / 10.f, _pObject->gc<CEnemy>()->m_fHeight / 2.f + RandRange(-_pObject->gc<CEnemy>()->m_fHeight * 5, _pObject->gc<CEnemy>()->m_fHeight * 5) / 10.f, 0), Vector3(0.002, 0.002, 0.002), "EFFECT_EXPLOSION");
				_pObject->gc<CEnemy>()->Hit(m_iDamage  * RandRange(80, 120) / 100.f);
				go->Destroy();
			}
		}
	}
}

void CPlayerBullet::Init(Vector3 _vPos,Vector3 _vDir, float _Speed, int _Damage)
{
	go->m_Tag = Tag::PlayerBulllet;
	ac<CMeshRenderer>()->Init(MESH("PLAYER_BULLET"));
	
	ac<CCollider>()->Init(1);
	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.25f, 0.25f, 0.5f);
	m_vDirection = _vDir;
	m_fSpeed = _Speed;
	m_iDamage = _Damage;
}
