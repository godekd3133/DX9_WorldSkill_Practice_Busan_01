#pragma once
#include "CComponent.h"
class CRenderer2D :
	public CComponent
{
public:
	CRenderer2D();
	virtual ~CRenderer2D();

public:
	virtual void Awake() PURE;
	virtual void Start() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void OnRender() PURE;
	virtual void OnDestroy() PURE;
	virtual void OnCollision() PURE;

public:
	Color m_Color;
	SortingLayer m_SortingLayer;
	Vector2 m_vAnchor = Vector2(0.5f,0.5f);
	Vector2 m_vFillAmount = Vector2(1.f, 1.f);
	RenderMode m_RenderMode;
};

