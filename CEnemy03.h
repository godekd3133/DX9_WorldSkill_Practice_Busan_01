#pragma once
#include "CComponent.h"
class CEnemy03 :
	public CComponent
{
public:
	CEnemy03();
	~CEnemy03();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(Vector3 _vPos);
	void OnAttack();
	void OnDead();

private:
	CEnemy * m_pEnemy = nullptr;
};

