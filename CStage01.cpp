#include "DXUT.h"
#include "CStage01.h"
#include "CPlayerUI.h"

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Init()
{
	GAME.Timer = 180;
	CGameObject * Map = OBJ.Create("Map", Tag::Map);
	list<CMesh*> listMap;
	listMap.push_back(MESH("MAP_STAGE02_PART01"));
	listMap.push_back(MESH("MAP_STAGE02_PART02"));
	listMap.push_back(MESH("MAP_STAGE02_PART03"));
	Map->ac<CStageMap>()->Init(listMap, SPRITE("MAP_STAGE01_MINIMAP"), SPRITE("MAP_STAGE01_MINIMAP"));
	GAME.m_pMap = Map->gc<CStageMap>();
	
	CGameObject * Player = OBJ.Create("Player", Tag::Player);
	Player->ac<CPlayerMovement>();
	Player->tf->m_vPos = Vector3(-5, 0, 5);
	GAME.m_pPlayer = Player;

	//CGameObject * PlayerUI = OBJ.Create();
	//PlayerUI->ac<CPlayerUI>();
}

void CStage01::Update()
{
	GAME.Timer -= dt;
	float distance = CAMERA.m_fDistance;
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(CAMERA.GetFinalPos()) == MapCollision::Wall)
	{
		CAMERA.m_fDistance = Lerp(CAMERA.m_fDistance, 0.f, dt * 8);
		if (GAME.m_pMap->GetCollisionInfoByCollisionMap(CAMERA.GetFinalPos()) == MapCollision::Floor)
			CAMERA.m_fDistance = distance;
	}
	else
	{
		CAMERA.m_fDistance = Lerp(CAMERA.m_fDistance, 6.f, dt *8);
		if (GAME.m_pMap->GetCollisionInfoByCollisionMap(CAMERA.GetFinalPos()) == MapCollision::Wall)
			CAMERA.m_fDistance = distance;
	}
}

void CStage01::Render()
{
	GRAPHICS.Render_Font(to_string(DXUTGetFPS()), GRAPHICS.ToMatrix(Vector3(100, 100, 0)), Color(1, 1, 1, 1), RenderMode::RM_UI);
}

void CStage01::Release()
{
}
