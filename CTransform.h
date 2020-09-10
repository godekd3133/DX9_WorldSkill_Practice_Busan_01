#pragma once
#include "CComponent.h"
class CTransform :
	public CComponent
{
public:
	CTransform();
	~CTransform();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	Vector3 m_vPos;
	Vector3 m_vScale;
	Quaternion m_quatRotation;

public:
	Vector3 GetWorldPos() {
		Vector3 vWorldPos = m_vPos;
		if (go->m_pParent)
			vWorldPos += go->m_pParent->tf->GetWorldPos();
		return vWorldPos;
	}
	Vector3 GetFoward();
	Vector3 GetRotation();
	void SetRotation(Vector3 _vRot);
	bool LerpRotation(Vector3 _vTarget, float _fTime);

	bool MoveToward(Vector3 _vTarget, float _fDist);
	bool LerpPosition(Vector3 _vTarget, float _fTime);

	bool LerpScale(Vector3 _vTarget, float _fTime);

	Matrix ToMatrix();
};

