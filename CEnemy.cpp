#include "DXUT.h"
#include "CEnemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Awake()
{
}

void CEnemy::Start()
{


}

void CEnemy::Update()
{

}

void CEnemy::LateUpdate()
{

}


void CEnemy::OnDestroy()
{
	
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
	
}

void CEnemy::Init(CMesh * _pMesh, int _Hp, int _Size)
{
	go->m_Tag = Tag::Enemy;
	ac<CMeshRenderer>()->Init(_pMesh);
	ac<CCollider>()->Init(_Size);

}
