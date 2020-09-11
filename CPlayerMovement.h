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


	Vector3 GetPlayerMoveDirectionFromInput();
	void FirePlayerBullet();

public:
	bool m_bFixPlayerRotation = false;

	float m_fTime = 0.f;
	float m_fDashTime = 0.f;
	Vector3 m_vVelocity = Vector3(0, 0, 0);
};

