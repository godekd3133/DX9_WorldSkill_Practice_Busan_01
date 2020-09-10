#pragma once
#include "CScene.h"
class CStageClear :
	public CScene
{
public:
	CStageClear();
	~CStageClear();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

