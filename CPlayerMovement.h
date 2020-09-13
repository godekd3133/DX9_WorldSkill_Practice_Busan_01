#pragma once
#include "CComponent.h"
class CPlayerMovement :
	public CComponent
{
public:
	CPlayerMovement();
	~CPlayerMovement();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

	void Move(Vector3 _vDirection, float _MoveSpeed, bool _WithRotation);
	string GetAnimationStateByWeapon();

	Vector3 GetPlayerMoveDirectionFromInput();
	void FirePlayerBullet();
	bool CanFireBullet();
	bool CanReload();
	void Reload();
public:
	bool m_bFixPlayerRotation = false;
	int m_iWeaponMode = 0;
	float m_fTime = 0.f;
	float m_fDashTime = 0.f;
	float m_fReloadTime = 0.f;
	float m_fReloadDelay = 1.5f;
	bool m_bReload = false;
	Vector3 m_vVelocity = Vector3(0, 0, 0);
};

