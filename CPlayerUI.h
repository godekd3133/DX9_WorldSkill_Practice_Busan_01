#pragma once
#include "CComponent.h"
class CPlayerUI :
	public CRenderer2D
{
public:
	CPlayerUI();
	~CPlayerUI();


public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnRender() override;
	virtual void OnCollision(CGameObject * _pObject) override;
	
	void RenderPlayer(CGameObject * _pPlayer);
	void RenderEnemy(CGameObject * _pEnemy);

};

