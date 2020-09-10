#pragma once
#include "CScene.h"
class CTitleScene :
	public CScene
{
public:
	CTitleScene();
	~CTitleScene();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
	CGameObject * m_pWindowInfo = nullptr;
	CGameObject * m_pWindowHowto = nullptr;
	CGameObject * m_pWindowRanking = nullptr;


	CGameObject * m_pBlack = nullptr;
	CGameObject * BT_Start;
	CGameObject * BT_Info;
	CGameObject * BT_Howto;
	CGameObject * BT_Ranking;
	CGameObject * BT_Exit;

};

