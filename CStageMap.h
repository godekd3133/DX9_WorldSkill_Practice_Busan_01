#pragma once
#include "CComponent.h"

enum MapCollision
{
	Floor,
	Wall,
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
	list<CMesh *> m_listMesh;
	CSprite * m_pMinimap = nullptr;
	CSprite * m_pCollisionMap = nullptr;
	void Init(list<CMesh *> _listMesh, CSprite * _pMinimap, CSprite * _pCollisionMap);
	MapCollision GetCollisionInfoByCollisionMap(Vector3 _vPos);

};

