#pragma once
#include "CScene.h"
class CGameOver :
	public CScene
{
public:
	CGameOver();
	~CGameOver();


public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	string text = "";

};

