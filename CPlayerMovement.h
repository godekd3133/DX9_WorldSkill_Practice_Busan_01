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
	virtual void OnCollision() override;

	void Move(Vector3 _vDirection, float _MoveSpeed);
	float Direction = 0.f;
	void OnLanding();
	bool TriggerAttackCombo = false;
	bool ChargingSkill01 = false;
	float ChargingTime = 0.f;
	int ZoomDir = 1;
	CGameObject * HandEffect = nullptr;
	CGameObject * Skill01Prepare = nullptr;

	void OnStopSkill01Rush();
};

