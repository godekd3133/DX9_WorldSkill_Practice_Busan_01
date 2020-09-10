#pragma once
#include "CRenderer2D.h"
class CText :
	public CRenderer2D
{
public:
	CText();
	~CText();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnRender() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	string m_Text = "";
	void Init(string _Text, SortingLayer _SortingLayer = SortingLayer::SR_Default, RenderMode _RenderMode = RenderMode::RM_Default, Color _Color = Color(1, 1, 1, 1));

};

