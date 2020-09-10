#pragma once
#include "CComponent.h"
class CRenderer3D :
	public CComponent
{
public:
	CRenderer3D();
	~CRenderer3D();

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
};

