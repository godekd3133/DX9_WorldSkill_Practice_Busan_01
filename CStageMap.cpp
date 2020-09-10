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

void CStageMap::Init(CMesh * _pMesh, CSprite * _pMinimap, CSprite * _pCollisionMap)
{
	m_pMesh = _pMesh;
	m_pMinimap = _pMinimap;
	m_pCollisionMap = _pCollisionMap;
	ac<CMeshRenderer>()->Init(m_pMesh);
	//CGameObject * pMinimap = OBJ.Create();
	//pMinimap->ac<CSpriteRenderer>()->Init(_pMinimap, SortingLayer::SR_Default, RenderMode::RM_UI);
	//pMinimap->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	//pMinimap->tf->m_vScale = Vector3(0.25f, 0.25f, 0.25f);
	tf->m_vScale = Vector3(-1.f, 1.f, 1.f);
	tf->m_vPos = Vector3(0, 0, 0);
}

MapCollision CStageMap::GetCollisionInfoByCollisionMap(Vector3 _vPos)
{
	D3DLOCKED_RECT lR;
	m_pCollisionMap->m_pTexture->LockRect(0, &lR, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lR.pBits);
	
	int PosX = (INT)(-_vPos.x /  10.f);
	int PosY = (INT)(_vPos.z / 10.f);
	

	if (PosX < 0 || PosX > m_pCollisionMap->m_Info.Width ||
		PosY < 0 || PosY > m_pCollisionMap->m_Info.Height)
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}

	D3DXCOLOR color = dwColor[(PosY * m_pCollisionMap->m_Info.Width ) + PosX];
//	dwColor[(PosY * m_pCollisionMap->m_Info.Width) + PosX] = Color(1, 1, 1, 1);
	//OutputDebugStringA(("r : " + to_string(color.r) + " g : "  + to_string(color.g) + " b : " + to_string(color.b) + " a : " + to_string(color.a) + "\n").c_str());
	//OutputDebugStringA(("X : " + to_string(PosX) + "Y" + to_string(PosY) +  "\n").c_str());

	if (color == Color(1, 0, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}
	else if (color == Color(1, 1, 0, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Between;
	}
	else if (color == Color(0, 1, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::SecondFloor;
	}
	m_pCollisionMap->m_pTexture->UnlockRect(0);
	return MapCollision::FirstFloor;
}

bool CStageMap::GetCollisionInfoByRay(Vector3 _vPos, Vector3 _vDir, float _Dist, CollisionInfo& Info)
{
	return true;//CAMERA.RayCast(gc<CMeshRenderer>(), _vPos, _vDir, _Dist, Info);
}

float CStageMap::GetFloorY(Vector3 _vPos)
{
	//CollisionInfo info;

	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(_vPos) == MapCollision::FirstFloor) return -800;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(_vPos) == MapCollision::SecondFloor) return -600;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(_vPos) == MapCollision::Between) return -700;

	//GetCollisionInfoByRay(_vPos  - Vector3(0,10000,0), Vector3(0, 1, 0), 100000000, info);


	//CollisionInfo info2;

	//GetCollisionInfoByRay(_vPos + Vector3(0, 10000, 0), Vector3(0, -1, 0), 100000000, info2);



	return 0;
}

