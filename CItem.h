#pragma once
#include "CComponent.h"
class CItem : public CComponent
{
public:
	CItem();
	~CItem();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;
};

