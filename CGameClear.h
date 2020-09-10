#pragma once
#include "CScene.h"
class CGameClear :
	public CScene
{
public:
	CGameClear();
	~CGameClear();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	string text = "";

};

