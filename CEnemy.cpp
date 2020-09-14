#include "DXUT.h"
#include "CEnemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Awake()
{
}

void CEnemy::Start()
{
	auto HpGaugeBG = OBJ.Create();
	if (m_bBoss == false)
		HpGaugeBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_BG"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
	else
		HpGaugeBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR_BG"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);

	go->AddChild(HpGaugeBG);
	HpGaugeBG->tf->m_vScale = Vector3(0.01f, 0.01f, 0.f);
	HpGaugeBG->tf->m_vScale.y = -HpGaugeBG->tf->m_vScale.y;
	HpGaugeBG->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGagueYellow = OBJ.Create();
	if (m_bBoss == false)
		m_pHpGagueYellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_YELLOW"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
	else
		m_pHpGagueYellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR_YELLOW"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
	go->AddChild(m_pHpGagueYellow);
	m_pHpGagueYellow->tf->m_vScale = Vector3(0.01f, 0.01f, 0.f);
	m_pHpGagueYellow->tf->m_vScale.y = -m_pHpGagueYellow->tf->m_vScale.y;
	m_pHpGagueYellow->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGague = OBJ.Create();
	if (m_bBoss == false)
		m_pHpGague->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
	else
		m_pHpGague->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);


	go->AddChild(m_pHpGague);
	m_pHpGague->tf->m_vScale = Vector3(0.01f, 0.01f, 0.f);
	m_pHpGague->tf->m_vScale.y = -m_pHpGague->tf->m_vScale.y;
	m_pHpGague->tf->m_vPos = Vector3(0, m_fHeight, 0);

	auto EnemyIcon = OBJ.Create();
	if (m_bBoss == false)
	{
		EnemyIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_MONSTER_HPICON"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
		EnemyIcon->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + 99.f / 77.f, 0.5f);

	}
	else
	{
		EnemyIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSS_HPICON"), SortingLayer::SR_BILBOARDUI, RenderMode::RM_Billboard);
		EnemyIcon->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + 199.f / 99.f, 0.5f);

	}
	go->AddChild(EnemyIcon);
	EnemyIcon->tf->m_vScale = Vector3(0.01f, 0.01f, 0.f);
	EnemyIcon->tf->m_vScale.y = -EnemyIcon->tf->m_vScale.y;
	EnemyIcon->tf->m_vPos = Vector3(0, m_fHeight, 0);





}

void CEnemy::Update()
{
	if(m_bIsDead == false)
	if (m_bVaccine)
	{
		list<CGameObject*> listEnemy = OBJ.Finds(Tag::Enemy);

		listEnemy.remove(go);

		if (listEnemy.empty() == false)
		{
			OBJ.SortByDistance(listEnemy);

			if (GetLength(tf->m_vPos,listEnemy.front()->tf->m_vPos) < m_fFindRange)
				m_pTarget = listEnemy.front();
		}
		else
			m_pTarget = nullptr;
	}
	else
	{
		if (m_pTarget == nullptr)
		{
			if (GetLength(tf->m_vPos, GAME.m_pPlayer->tf->m_vPos) < m_fFindRange)
				m_pTarget = GAME.m_pPlayer;
			else
				m_pTarget = nullptr;
		}
	}

	m_pHpGague->gc<CSpriteRenderer>()->m_vFillAmount = Vector2((float)m_iCurHp / (float)m_iMaxHp, 1.f);
	m_pHpGagueYellow->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pHpGagueYellow->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)m_iCurHp / (float)m_iMaxHp, 1.f), dt  * 6.f);

	m_pShadow->tf->m_vPos = Vector3(tf->m_vPos.x, 0.1f, tf->m_vPos.z);

	float scale = (gc<CCollider>()->m_fRadius *100.f)  / max(abs(0 - tf->m_vPos.y), 100);
	m_pShadow->tf->m_vScale = Vector3(scale, scale, 1.f) / 100.f;
}

void CEnemy::LateUpdate()
{

}


void CEnemy::OnDestroy()
{
	m_pShadow->Destroy();
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
	
}

void CEnemy::Init(CMesh * _pMesh, int _Hp, float _Size, float _FindRange, float _AttackRange, float _MoveSpeed, float _Height)
{
	go->m_Tag = Tag::Enemy;
	ac<CMeshRenderer>()->Init(_pMesh);
	ac<CCollider>()->Init(_Size);

	m_iCurHp = _Hp;
	m_iMaxHp = _Hp;

	m_fAttackRange = _AttackRange;
	m_fFindRange = _FindRange;
	m_fMoveSpeed = _MoveSpeed;

	m_bIsDead = false;
	m_bVaccine = false;

	m_fHeight = _Height;
	m_pShadow = OBJ.Create();
	m_pShadow->ac<CSpriteRenderer>()->Init(SPRITE("UI_SHADOW"), SortingLayer::SR_UI, RenderMode::RM_Default);
	m_pShadow->tf->SetRotation(Vector3(90, 0, 0));
}

void CEnemy::Hit(int _Damage)
{
	if (m_bIsDead == false)
	{
		m_iCurHp -= _Damage;
		OnHit(_Damage);
		if (m_bVaccine == false)
		{
			m_pTarget = GAME.m_pPlayer;
		}
		if (m_iCurHp <= 0)
		{
			OnDead();
			m_bIsDead = true;
		}
	}
}

void CEnemy::Move(Vector3 _vDirection, float _MoveSpeed)
{
	Vector3 OldPos = tf->m_vPos;

	if (_vDirection.x > 0)
		_vDirection.x = max(_vDirection.x, 0.2f);
	else if (_vDirection.x < 0)
		_vDirection.x = min(_vDirection.x, -0.2f);
	if (_vDirection.z > 0)
		_vDirection.z = max(_vDirection.z, 0.2f);
	else if (_vDirection.z< 0)
		_vDirection.z = min(_vDirection.z, -0.2f);

	tf->LerpRotation(Vector3(0, my::GetDirAngle(_vDirection), 0), dt * 8);

	tf->m_vPos.x += _vDirection.x *  dt * _MoveSpeed;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		tf->m_vPos.x = OldPos.x;
	}

	tf->m_vPos.z += _vDirection.z *  dt * _MoveSpeed;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall)
	{
		tf->m_vPos.z = OldPos.z;
	}

}



void CEnemy::OnHit(int _Damage)
{
	gc<CMeshRenderer>()->sa->Clear();
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {
		return gc<CMeshRenderer>()->LerpColor(Color(1, 0, 0, 1), 36 * dt);
	});
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {
		return gc<CMeshRenderer>()->LerpColor(Color(1, 1, 1, 1), 36 * dt);
	});


	CGameObject * DamageFont = OBJ.Create();
	DamageFont->tf->m_vScale = Vector3(0.01, 0.01, 0.01);
	DamageFont->ac<CDamageFont>()->Init("UI_ENEMY_DAMAGEFONT", tf->m_vPos + Vector3 (RandRange(-100,100)/100.f, m_fHeight/2.f + RandRange(-100,100)/100.f,0), _Damage);

}

