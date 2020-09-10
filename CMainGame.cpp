#include "DXUT.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CStage01.h"
#include "CStageClear.h"
#include "CStage02.h"
#include "CGameClear.h"
#include "CGameOver.h"

CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{

	std::future<void> a =
		std::async(launch::async, [=]() {
		AddMesh("MAP_STAGE01", "Player/Pistol/Idle/Idle", "Player", 1);//21);
		AddSprite("MAP_STAGE01_MINIMAP", "map/1-1stage/mapnormal");

		AddMesh("MAP_STAGE02_1", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		AddMesh("MAP_STAGE02_2", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		AddMesh("MAP_STAGE02_3", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		AddSprite("MAP_STAGE02_MINIMAP", "map/2-1stage/mapnormal");

		AddMesh("PLAYER_PISTOL_IDLE", "Player/Pistol/Idle/Idle","Player",			1);//21);
		AddMesh("PLAYER_PISTOL_RUN", "Player/Pistol/Run/Run", "Player",				1);//21);
		AddMesh("PLAYER_PISTOL_SHOOT", "Player/Pistol/Shoot/Shoot", "Player",		1);//16);
		AddMesh("PLAYER_PISTOL_SKILL", "Player/Pistol/Skill/Skill", "Player",		1);//26);
		AddMesh("PLAYER_PISTOL_WALK", "Player/Pistol/Walk/Walk", "Player",			1);//21);
		AddMesh("PLAYER_RIFLE_IDLE", "Player/Rifle/Idle/Idle", "Player",			1);//21);
		AddMesh("PLAYER_RIFLE_RUN", "Player/Rifle/Run/Run", "Player",				1);//21);
		AddMesh("PLAYER_RIFLE_SHOOT", "Player/Rifle/Shoot/Shoot", "Player",			1);//16);
		AddMesh("PLAYER_RIFLE_SKILL", "Player/Rifle/Skill/Skill", "Player",			1);//26);
		AddMesh("PLAYER_RIFLE_WALK", "Player/Rifle/Walk/Walk", "Player",			1);//21);

		AddMesh("ENEMY_01_IDLE", "monster1/Idle/Idle", "monster1",					1);//61);
		AddMesh("ENEMY_01_WALK", "monster1/Walk/Walk", "monster1",					1);//31);
		AddMesh("ENEMY_01_ATTACK", "monster1/att1/Attack", "monster1",				1);//26);

		AddMesh("ENEMY_02_IDLE", "monster2/Idle/Idle", "monster2",					1);//41);
		AddMesh("ENEMY_02_WALK", "monster2/Walk/Walk", "monster2",					1);//41);
		AddMesh("ENEMY_02_ATTACK", "monster2/att1/Attack", "monster2",				1);//31);
		AddMesh("ENEMY_02_DEAD", "monster2/Dead/Dead", "monster2",					1);//41);

		AddMesh("ENEMY_03_IDLE", "monster3/Idle/Idle", "monster3",					1);//51);
		AddMesh("ENEMY_03_WALK", "monster3/Walk/Walk", "monster3",					1);//36);
		AddMesh("ENEMY_03_ATTACK", "monster3/att1/Attack", "monster3",				1);//36);
		AddMesh("ENEMY_03_DEAD", "monster3/Dead/Dead", "monster3",					1);//44);

		AddMesh("BOSS_01_IDLE", "Boss/Idle/Idle", "Boss",							1);//43);
		AddMesh("BOSS_01_WALK", "Boss/Walk/Walk", "Boss",							1);//43);
		AddMesh("BOSS_01_ATTACK_01", "Boss/att1/Attack01", "Boss",					1);//53);
		AddMesh("BOSS_01_ATTACK_02", "Boss/att2/Attack02", "Boss",					1);//46);
		AddMesh("BOSS_01_SKILL", "Boss/Skill/Skill", "Boss",						1);//83);
		AddMesh("BOSS_01_DEAD", "Boss/Dead/Dead", "Boss",							1);//74);
		AddMesh("BOSS_01_BORN", "Boss/Born/Born", "Boss",							1);//118);

		AddMesh("BOSS_02_IDLE", "Boss2/Idle/Idle", "Boss",							1);//36);
		AddMesh("BOSS_02_WALK", "Boss2/Walk/Walk", "Boss",							1);//33);
		AddMesh("BOSS_02_ATTACK_01", "Boss2/att1/Attack01", "Boss",					1);//53);
		AddMesh("BOSS_02_ATTACK_02", "Boss2/att2/Attack02", "Boss",					1);//146);
		AddMesh("BOSS_02_SKILL", "Boss2/Skill/Skill", "Boss",						1);//83);
		AddMesh("BOSS_02_DEAD", "Boss2/Dead/Dead", "Boss",							1);//74);
		AddMesh("BOSS_02_BORN", "Boss2/Born/Born", "Boss",							1);//118);
	});

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.AddScene("S_STAGE01", new CStage01());
	SCENE.AddScene("S_STAGECLEAR", new CStageClear());
	SCENE.AddScene("S_STAGE02", new CStage02());
	SCENE.AddScene("S_GAMECLEAR", new CGameClear());
	SCENE.AddScene("S_GAMEOVER", new CGameOver());
	SCENE.ChangeScene("S_TITLE");

}

void CMainGame::Update()
{
	INPUT.Update();

	SCENE.Update();

	OBJ.Update();

	CAMERA.Update();

	INPUT.TimeScale = Lerp(INPUT.TimeScale, 1.f, udt * 10);
}

void CMainGame::Render()
{

	CAMERA.SetTransform();


	OBJ.Render();
	SCENE.Render();
}

void CMainGame::Release()
{
	CInputManager::ReleaseInstance();
	CGraphicsManager::ReleaseInstance();
	CSceneManager::ReleaseInstance();
	CObjectManager::ReleaseInstance();
	CCameraManager::ReleaseInstance();
}

void CMainGame::OnLostDevice()
{
	GRAPHICS.OnLostDevice();
}

void CMainGame::OnResetDevice()
{
	GRAPHICS.OnResetDevice();
}

void CMainGame::AddSprite(string _Key, string _Path, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".png";
		GRAPHICS.AddSprite(Key, Path);
	}
	else
	{
		for (int i = 0; i < _Count; i++)
		{
			string Key = _Key + " (" + to_string(i + 1) + ")";
			string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").png";
			GRAPHICS.AddSprite(Key, Path);

		}
	}
}

void CMainGame::AddMesh(string _Key, string _Path, string _MapPath, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".obj";
		string MapPath = "./resource/" + _MapPath + "/";
		GRAPHICS.AddMesh(Key, Path, MapPath);
	}
	else
	{
			for (int i = 0; i < _Count; i++)
		{


					string Key = _Key + " (" + to_string(i + 1) + ")";
					string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
					string MapPath = "./resource/" + _MapPath + "/";
					GRAPHICS.AddMesh(Key, Path, MapPath);
		}

	}
}
