#pragma once
#include "CSingleton.h"
class CObjectManager :
	public CSingleton< CObjectManager>
{
	friend class CRenderer2D;
	friend class CRenderer3D;
	friend class CCollider;
public:
	CObjectManager();
	~CObjectManager();

private:
	list<CGameObject*> m_listGameObject;
	list<CRenderer2D *> m_listRenderer2D;
	list<CRenderer3D *> m_listRenderer3D;
	list<CCollider * > m_listCollider3D;

public:
	void Clear();
	void Update();
	void Render();
	CGameObject* Create(string _Name = "go", Tag _Tag = Tag::Untagged);

	bool IsCollision(CCollider * _Prev, CCollider * _Next);

	CGameObject * Find(string _Name);
	CGameObject * Find(Tag _Tag);
	list <CGameObject * >Finds(string _Name);
	list <CGameObject * >Finds(Tag _Tag);



	list<CGameObject *> GetCollisionObject(Vector3 _vPos, float _Radius, Tag _Tag);
	list<CGameObject *> GetCollisionObject(Vector3 _vPos, float _Radius);

	list<CGameObject *> RayCast(Vector3 _vPos, Vector3 _vDir, float _fDist = -1.f);
	list<CGameObject *> RayCast(Vector3 _vPos, Vector3 _vDir, Tag _TagMask, float _fDist = -1.f);

	void SortByDistance(list<CGameObject*>& _listObject);
};

#define OBJ (*CObjectManager::GetInstance())