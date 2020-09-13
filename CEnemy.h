#pragma once
#include "CComponent.h"

enum class ENEMY_STATE
{
	IDLE,
	WALK,
	CHASE,
	ATTACK_PREPARE,
	ATTACK
};

class CEnemy :
	public CComponent
{
public:
	CEnemy();
	~CEnemy();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(CMesh * _pMesh , int _Hp, float _Size, float _FindRange, float _AttackRange, float _MoveSpeed, float _Height);
	void Hit(int _Damage);
	void Move(Vector3 _vDirection, float _MoveSpeed);
	Event OnDead;
	void OnHit(int _Damage);

public:
	bool m_bBoss = false;
	int m_iMaxHp;
	int m_iCurHp;
	float m_fFindRange;
	float m_fAttackRange;
	float m_fMoveSpeed ;
	bool m_bVaccine = false;
	bool m_bIsDead = true;
	float m_fHeight;
public:
	CGameObject * m_pTarget = nullptr;

	CGameObject * m_pHpGague = nullptr;
	CGameObject * m_pHpGagueYellow = nullptr;
	CGameObject * m_pShadow = nullptr;
};

