#pragma once
#include "CComponent.h"

enum class Enemy_State
{
	IDLE, CHASE, ATTACK_PREPARE ,ATTACK
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
};

