#pragma once
#include "CComponent.h"
class CAnimator2D :
	public CComponent
{
public:
	CAnimator2D();
	~CAnimator2D();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

private:
	CSpriteRenderer * SpriteRenderer;
	map<string, CAnimation2D * > m_mapAnimation;
	CAnimation2D * m_pCurrentState;
public:
	void SetCurrentState(string _State);
	CAnimation2D* GetState(string _State);
	CAnimation2D* GetCurrentState();

	void AddState(string _StateName, string _ResourceKey, float _Delay, bool _Repeat = true);

};

