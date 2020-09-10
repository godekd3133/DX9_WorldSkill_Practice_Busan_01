#pragma once
#include "CComponent.h"

enum MapCollision
{
	FirstFloor,
	Wall,
	Between,
	SecondFloor
};

struct CollisionInfo
{
	Vector3 vPos;
	float distance;
};
class CStageMap :
	public CComponent
{
public:
	CStageMap();
	~CStageMap();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

private:
	CGameObject * m_pPlayer = nullptr;
public:
	CMesh * m_pMesh = nullptr;
	CSprite * m_pMinimap = nullptr;
	CSprite * m_pCollisionMap = nullptr;
	void Init(CMesh * _pMesh, CSprite * _pMinimap, CSprite * _pCollisionMap);
	MapCollision GetCollisionInfoByCollisionMap(Vector3 _vPos);
	bool GetCollisionInfoByRay(Vector3 _vPos, Vector3 _vDir, float _Dist, CollisionInfo& Info);

	float GetFloorY(Vector3 _vPos);
};

