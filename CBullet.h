#pragma once
#include "CComponent.h"
class CBullet :
	public CComponent
{
public:
	CBullet();
	~CBullet();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision() override;

public:
	void Init(Vector3 _vPos, Vector3 _vDir, float _fSpeed);
	float m_fSpeed;
	Vector3 m_vDirection;
};

