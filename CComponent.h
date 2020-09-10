#pragma once
#include "CGameObject.h"
class CComponent
{
public:
	CComponent();
	virtual ~CComponent();

public:
	virtual void Awake() PURE;
	virtual void Start() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void OnDestroy() PURE;
	virtual void OnCollision(CGameObject * _pObject) PURE;

public:
	bool m_bStart = false;
	bool m_bEnable = true;
	CGameObject * go;
	CTransform * tf;
	CScheduleAdmin * sa;

public:
	template <class T>
	T  *gc() { return go->gc<T>(); }
	template <class T>
	T  *ac() { return go->ac<T>(); }

};

