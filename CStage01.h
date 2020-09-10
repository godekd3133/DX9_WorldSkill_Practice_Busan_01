#pragma once
#include "CScene.h"
class CStage01 :
	public CScene
{
public:
	CStage01();
	~CStage01();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_fTime = 0.f;

	int idx = 0;
};

