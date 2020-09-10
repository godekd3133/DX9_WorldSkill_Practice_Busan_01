#pragma once
#include "CComponent.h"
class CRigidBody :
	public CComponent
{
public:
	CRigidBody();
	~CRigidBody();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;
	
public:
	Vector3 m_vVelocity;
	Vector3 m_vOldPos;
	float Offset = 0.f;
	bool m_bGravity = true;
	Vector3 m_vImpulse = Vector3(8.f,0.f,8.f);
public:
	void AddForce(Vector3 _vVelocitiy, Vector3 _vImpulse = Vector3(8.f, 0.f, 8.f));
	CStageMap * m_pMap = nullptr;

};

