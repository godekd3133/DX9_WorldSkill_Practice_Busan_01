#include "DXUT.h"
#include "CStageMap.h"

CStageMap::CStageMap()
{
}


CStageMap::~CStageMap()
{
}

void CStageMap::Awake()
{
}

void CStageMap::Start()
{
	//m_pPlayer = OBJ.Create();
	//m_pPlayer->ac<CSpriteRenderer>()->Init(SPRITE("MAP_STAGE01_PLAYER"), SortingLayer::SR_Effect, RenderMode::RM_UI);
	

}

void CStageMap::Update()
{
	//Vector3 _vPos = OBJ.Find(Tag::Player)->tf->GetWorldPos();
	//int PosX = (INT)(-_vPos.x / 10.f);
	//int PosY = (INT)(_vPos.z / 10.f);
	//m_pPlayer->tf->m_vPos = Vector3(PosX, PosY, 0.f);
}

void CStageMap::LateUpdate()
{
}

void CStageMap::OnDestroy()
{
}

void CStageMap::OnCollision(CGameObject * _pObject)
{
}

void CStageMap::Init(list<CMesh *> _listMesh, CSprite * _pMinimap, CSprite * _pCollisionMap)
{
	m_listMesh = _listMesh;
	m_pMinimap = _pMinimap;
	m_pCollisionMap = _pCollisionMap;
	for (auto iter: _listMesh)
	{
		CGameObject * pMap = OBJ.Create("MAP",Tag::Map);
		pMap->ac<CMeshRenderer>()->Init(iter);
		go->AddChild(pMap);
		pMap->tf->m_vScale = Vector3(1.f, 1.f, 1.f);
	}

	tf->m_vPos = Vector3(0, 0, 0);
}

MapCollision CStageMap::GetCollisionInfoByCollisionMap(Vector3 _vPos)
{
	return MapCollision::Floor;
	D3DLOCKED_RECT lR;
	m_pCollisionMap->m_pTexture->LockRect(0, &lR, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lR.pBits);
	
	int PosX = (INT)(-_vPos.x *  10.f);
	int PosY = (INT)(_vPos.z * 10.f);
	

	if (PosX < 0 || PosX > m_pCollisionMap->m_Info.Width ||
		PosY < 0 || PosY > m_pCollisionMap->m_Info.Height)
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}

	D3DXCOLOR color = dwColor[(PosY * m_pCollisionMap->m_Info.Width ) + PosX];

	if (color == Color(1, 0, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Floor;
	}
	else if (color == Color(1, 1, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}
	//else if (color == Color(0, 1, 1, 1))
	//{
	//	m_pCollisionMap->m_pTexture->UnlockRect(0);
	//	return MapCollision::SecondFloor;
	//}
	//m_pCollisionMap->m_pTexture->UnlockRect(0);
	return MapCollision::Wall;
}





