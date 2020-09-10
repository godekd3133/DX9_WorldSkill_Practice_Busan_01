#pragma once
#include "CComponent.h"
class CButton :
	public CComponent
{
public:
	CButton();
	~CButton();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;


public:
	void Init(CSprite * _pSprite, Vector3 _vPos, Vector3 _vScale, function<void()> _OnClick);

private:
	function<void()> m_OnClick;
	Vector3 m_vStartScale;
	RECT m_reRect;
};

