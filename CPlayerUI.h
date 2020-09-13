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

	CGameObject * CurrentWeapon;
	CGameObject * CurrentBullet_Text;
	CGameObject * HavingBullet_Text;


	CGameObject * m_pHpBar;
	CGameObject * m_pHpBar_Bg;
	CGameObject * m_pHpBar_Yellow;
	CGameObject * m_pLevelText;
	CGameObject * m_pExpBar;
	CGameObject * m_pExpBar_Bg;
	
	CGameObject * m_pTimer_Text;


	CGameObject * m_pSkill01;
	CGameObject * m_pSkill02;
	CGameObject * m_pSkill03;
	CGameObject * m_pSkill04;


};

