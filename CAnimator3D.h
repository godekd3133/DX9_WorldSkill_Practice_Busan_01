#pragma once
#include "CComponent.h"
class CAnimator3D :
	public CComponent
{
public:
	CAnimator3D();
	~CAnimator3D();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

private:
	CMeshRenderer * MeshRenderer;
	map<string, CAnimation3D * > m_mapAnimation;
	CAnimation3D * m_pCurrentState;
public:
	void SetCurrentState(string _State);
	CAnimation3D* GetState(string _State);
	CAnimation3D* GetCurrentState();

	void AddState(string _StateName, string _ResourceKey, float _Delay, bool _Repeat = true);
	
};

