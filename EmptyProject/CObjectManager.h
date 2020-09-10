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
	list<CRenderer2D *> m_listRenderer2D;
	list<CRenderer3D *> m_listRenderer3D;
	list<CCollider * > m_listCollider3D;

};

#define OBJ (*CObjectManager::GetInstance())