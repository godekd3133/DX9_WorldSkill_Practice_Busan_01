#pragma once
#include "CRenderer2D.h"
class CSpriteRenderer :
	public CRenderer2D
{
public:
	CSpriteRenderer();
	~CSpriteRenderer();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnRender() override;
	virtual void OnDestroy() override;
	virtual void OnCollision() override;

public:
	CSprite * m_pSprite;

public:
	void Init(CSprite * _pSprite, SortingLayer _SortingLayer = SortingLayer::SR_Default , RenderMode _RenderMode = RenderMode::RM_Default, Color _Color = Color(1, 1, 1, 1));

};

