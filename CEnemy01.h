#pragma once
#include "CComponent.h"
class CEnemy01 :
	public CComponent
{
public:
	CEnemy01();
	~CEnemy01();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(Vector3 _vPos);
private:
	CEnemy * m_pEnemy = nullptr;
};

