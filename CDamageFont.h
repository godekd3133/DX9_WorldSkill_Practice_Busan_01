#pragma once
#include "CComponent.h"
class CDamageFont :
	public CComponent
{
public:
	CDamageFont();
	~CDamageFont();
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(string _Key, Vector3 _vPos, int _Damage);
	void InitCombo(string _Key, Vector3 _vPos, int _Combo);
	void SetAlpha(float _Alpha);
	float GetAlpha();
	void SetTransform();
	Vector2 m_vSize;

private:
	vector<CGameObject *> m_vecFontObject;
};

