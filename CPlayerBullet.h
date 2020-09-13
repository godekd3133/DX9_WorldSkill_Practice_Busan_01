#pragma once
#include "CComponent.h"
class CPlayerBullet :
	public CComponent
{
public:
	CPlayerBullet();
	~CPlayerBullet();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

	void Init(Vector3 _vPos, Vector3 _vDir, float _Speed, int _Damage);

private:
	Vector3 m_vDirection;
	float m_fSpeed;
	int m_iDamage;
	float m_fTime = 0.f;
};

