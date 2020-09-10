#include "DXUT.h"
#include "CTitleScene.h"
#include "CPlayerMovement.h"

CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	CGameObject * pMap = OBJ.Create("Map",Tag::Map);
	pMap->ac<CMeshRenderer>()->Init(MESH("MAP_STAGE01"));
	pMap->tf->m_vScale = Vector3(-1.f, 1.f, 1.f);
	pMap->tf->m_quatRotation = QuatEular(Vector3(0, 180, 0));
	pMap->tf->m_vPos = Vector3(0,0, 0);

	CGameObject * pPlayer = OBJ.Create();
	pPlayer->ac<CPlayerMovement>();
	pPlayer->tf->m_vPos = Vector3(0, 0, 0);
}

void CTitleScene::Update()
{
}

void CTitleScene::Render()
{
}

void CTitleScene::Release()
{
}
