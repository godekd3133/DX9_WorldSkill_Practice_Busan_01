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

	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		go->Destroy();
	}
}

void CPlayerBullet::LateUpdate()
{
}

void CPlayerBullet::OnDestroy()
{
	EFFECT(tf->m_vPos, Vector3(0.002, 0.002, 0.003), "EFFECT_EXPLOSION");
}

void CPlayerBullet::OnCollision(CGameObject * _pObject)
{
	if (_pObject->m_Tag == Tag::Enemy)
	{
		go->Destroy();
	}

}

void CPlayerBullet::Init(Vector3 _vPos,Vector3 _vDir, float _Speed)
{
	ac<CMeshRenderer>()->Init(MESH("PLAYER_BULLET"));
	ac<CCollider>()->Init(1);
	tf->m_vPos = _vPos;
	m_vDirection = _vDir;
	m_fSpeed = _Speed;
}
