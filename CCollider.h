#pragma once
#include "CComponent.h"
class CCollider :
	public CComponent
{
public:
	CCollider();
	~CCollider();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(float _fRadius);
	float m_fRadius;	

	LPD3DXMESH Sphere;

};

