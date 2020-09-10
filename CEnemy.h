#pragma once
#include "CComponent.h"
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
	virtual void OnCollision() override;

public:
	int m_iCurHp;
	int m_iMaxHp;

	void OnHit(int _Damage);


};

