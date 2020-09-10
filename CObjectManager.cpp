#include "DXUT.h"
#include "CObjectManager.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
	for (auto iter : m_listGameObject)
	{
		for (auto comp : iter->m_listComponent)
		{
			comp->OnDestroy();
		}
		for (auto comp2 : iter->m_listComponent)
		{
			SAFE_DELETE(comp2);
		}
		iter->m_listComponent.clear();

		SAFE_DELETE(iter);
	}
	m_listGameObject.clear();
}

void CObjectManager::Clear()
{
	for (auto iter : m_listGameObject)
	{
		for (auto comp : iter->m_listComponent)
		{
			comp->OnDestroy();
		}
		for (auto comp2 : iter->m_listComponent)
		{
			SAFE_DELETE(comp2);
		}
		iter->m_listComponent.clear();

		SAFE_DELETE(iter);
	}
	m_listGameObject.clear();
}

void CObjectManager::Update()
{
	for (auto iter : m_listGameObject)
	{
		for (auto comp : iter->m_listComponent)
		{
			if (comp->m_bStart == false)
			{
				comp->m_bStart = true;
				comp->Start();
			}
		}

		if (iter->m_bEnable)
			for (auto comp : iter->m_listComponent)
			{
				if (comp->m_bEnable)
				{
					comp->sa->Update();
				comp->Update();

				}
			}
	}
	for (auto iter = m_listCollider3D.begin(); iter != m_listCollider3D.end(); iter++)
	{
		for (auto iter2 = std::next(iter); iter2 != m_listCollider3D.end(); iter2++)
		{
			if (IsCollision(*iter, *iter2))
			{
				for(auto comp : (*iter)->go->m_listComponent)
				{
					comp->OnCollision((*iter2)->go);
				}
				for (auto comp : (*iter2)->go->m_listComponent)
				{
					comp->OnCollision((*iter)->go);
				}
			}
		}
	}


	for (auto iter : m_listGameObject)
	{
		if (iter->m_bEnable)
			for (auto comp : iter->m_listComponent)
			{
				if (comp->m_bEnable)
					comp->LateUpdate();
			}
	}

	for (auto iter = m_listGameObject.begin(); iter != m_listGameObject.end(); )
	{
		if ((*iter)->m_bDestroy == true)
		{


			SAFE_DELETE(*iter);
			iter = m_listGameObject.erase(iter);
		}
		else iter++;
	}
}

void CObjectManager::Render()
{
	for (auto iter : m_listRenderer3D)
	{
		if(iter->go->m_Tag == Tag::Map)
		g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		if (iter->m_bEnable)
		{
			iter->OnRender();
		}
		g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	}

	m_listRenderer2D.sort([](CRenderer2D * _Prev, CRenderer2D * _Next)->bool {
		return (int)_Prev->m_SortingLayer < (int)_Next->m_SortingLayer;
	});

	for (auto iter : m_listRenderer2D)
	{
		if (iter->m_bEnable)
			iter->OnRender();
	}
}

CGameObject * CObjectManager::Create(string _Name, Tag _Tag)
{
	CGameObject * pObject = new CGameObject();
	pObject->m_Tag = _Tag;
	pObject->m_Name = _Name;
	pObject->tf = pObject->ac<CTransform>();

	m_listGameObject.push_back(pObject);
	return pObject;
}

bool CObjectManager::IsCollision(CCollider * _Prev, CCollider * _Next)
{
	return my::GetLength(_Prev->tf->GetWorldPos(), _Next->tf->GetWorldPos()) < _Prev->m_fRadius + _Next->m_fRadius;
}

CGameObject * CObjectManager::Find(string _Name)
{
	for (auto iter : m_listGameObject)
		if (iter->m_Name == _Name)
			return iter;
	return nullptr;
}

CGameObject * CObjectManager::Find(Tag _Tag)
{
	for (auto iter : m_listGameObject)
		if (iter->m_Tag == _Tag)
			return iter;
	return nullptr;
}

list <CGameObject * > CObjectManager::Finds(string _Name)
{
	list <CGameObject * > listFind;
	for (auto iter : m_listGameObject)
		if (iter->m_Name == _Name)
			listFind.push_back(iter);
	return listFind;
}

list <CGameObject * >CObjectManager::Finds(Tag _Tag)
{
	list <CGameObject*> listFind;
	for (auto iter : m_listGameObject)
		if (iter->m_Tag == _Tag)
			listFind.push_back(iter);
	return listFind;
}

list<CGameObject*> CObjectManager::GetCollisionObject (Vector3 _vPos, float _Radius, Tag _Tag)
{
	list<CGameObject*> listCollision; 

	CGameObject * pCollision = Create();

	pCollision->ac<CCollider>()->Init(_Radius);

	CCollider* Collider = pCollision->gc<CCollider>();

	pCollision->tf->m_vPos = _vPos;
	
	for (auto iter : m_listCollider3D)
	{
			if(iter->go->m_Tag == _Tag)
			if (IsCollision(iter, Collider))
				listCollision.push_back(iter->go);
	}
	pCollision->Destroy();

	return listCollision;
}

list<CGameObject*> CObjectManager::GetCollisionObject(Vector3 _vPos, float _Radius)
{
	list<CGameObject*> listCollision;

	CGameObject * pCollision = Create();

	pCollision->ac<CCollider>()->Init(_Radius);

	CCollider* Collider = pCollision->gc<CCollider>();

	pCollision->tf->m_vPos = _vPos;

	for (auto iter : m_listCollider3D)
	{
		if (iter->go != pCollision )
		{
			if (IsCollision(iter, Collider))
				listCollision.push_back(iter->go);
		}
	}
	pCollision->Destroy();

	return listCollision;
}

list<CGameObject *>  CObjectManager::RayCast(Vector3 _vPos, Vector3 _vDir, float _fDist)
{
	CollisionInfo info;
	list<CGameObject*> CollisionObject;
	for (auto iter : m_listCollider3D)
	{
		bool res ;
		if (_fDist == -1.f)
			res = CAMERA.RayCastAtSphere(iter->Sphere, iter->tf->ToMatrix(), _vPos, _vDir, 1000000000, info);
		else 
			res = CAMERA.RayCastAtSphere(iter->Sphere, iter->tf->ToMatrix(), _vPos, _vDir, _fDist, info);
	
		if (res == true)
			CollisionObject.push_back(iter->go);
	}
	
	return CollisionObject;
}

list<CGameObject *> CObjectManager::RayCast(Vector3 _vPos, Vector3 _vDir, Tag _TagMask, float _fDist)
{
	CollisionInfo info;
	list<CGameObject*> CollisionObject;
	for (auto iter : m_listCollider3D)
	{
		if (_TagMask != iter->go->m_Tag) continue;
		bool res;
		if (_fDist == -1.f)
			res = CAMERA.RayCastAtSphere(iter->Sphere, iter->tf->ToMatrix(), _vPos, _vDir, 1000000000, info);
		else
			res = CAMERA.RayCastAtSphere(iter->Sphere, iter->tf->ToMatrix(), _vPos, _vDir, _fDist, info);

		if (res == true)
			CollisionObject.push_back(iter->go);
	}

	return CollisionObject;
}

void CObjectManager::SortByDistance(list<CGameObject*>& _listObject)
{
	_listObject.sort([](CGameObject * _Prev, CGameObject * _Next)->bool 
	{
		float dist1 = GetLength(_Prev->tf->m_vPos, Vector3(0, 0, 0));
		float dist2 = GetLength(_Next->tf->m_vPos, Vector3(0, 0, 0));

		return dist1 < dist2;
	}
	);
}


