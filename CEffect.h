#pragma once
#include "CComponent.h"
class CEffect :
	public CComponent
{
public:
	CEffect();
	~CEffect();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision() override;

public:
	void Init(string _ResKey, float _Delay, Vector3 _vPos);
};

