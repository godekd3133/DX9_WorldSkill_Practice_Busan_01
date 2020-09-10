#pragma once
#include "CScene.h"
class CStage02 :
	public CScene
{
public:
	CStage02();
	~CStage02();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	float m_fTime = 0.f;
	int idx = 0;
};

