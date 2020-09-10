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
	void Update();
	void Render();
	CGameObject* Create(string _Name = "go", Tag _Tag = Tag::Untagged);

	bool IsCollision(CCollider * _Prev, CCollider * _Next);

	CGameObject * Find(string _Name);
	CGameObject * Find(Tag _Tag);
	list <CGameObject * >Finds(string _Name);
	list <CGameObject * >Finds(Tag _Tag);
};

#define OBJ (*CObjectManager::GetInstance())