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

	AddMesh("MAP_STAGE01", "map/1-1stage/1stage_reamke", "map/1-1stage");//21);
	AddSprite("MAP_STAGE01_MINIMAP", "map/1-1stage/mapnormal");

	AddMesh("PLAYER_BULLET", "bullet", "");

	AddSprite("EFFECT_EXPLOSION", "Effect/Explosion/Explosion", 8);//21);


	AddMesh("MAP_STAGE02_1", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage");
	AddMesh("MAP_STAGE02_2", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage");
	AddMesh("MAP_STAGE02_3", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage");
	AddSprite("MAP_STAGE02_MINIMAP", "map/2-1stage/mapnormal");

	AddMesh("PLAYER_PISTOL_IDLE", "Player/Pistol/Idle/Idle", "Player", 21);
	AddMesh("PLAYER_PISTOL_RUN", "Player/Pistol/Run/Run", "Player", 21);
	AddMesh("PLAYER_PISTOL_SHOOT", "Player/Pistol/Shoot/Shoot", "Player", 16);
	AddMesh("PLAYER_PISTOL_SKILL", "Player/Pistol/Skill/Skill", "Player", 26);
	AddMesh("PLAYER_PISTOL_WALK", "Player/Pistol/Walk/Walk", "Player", 21);
	AddMesh("PLAYER_RIFLE_IDLE", "Player/Rifle/Idle/Idle", "Player", 21);
	AddMesh("PLAYER_RIFLE_RUN", "Player/Rifle/Run/Run", "Player", 21);
	AddMesh("PLAYER_RIFLE_SHOOT", "Player/Rifle/Shoot/Shoot", "Player", 16);
	AddMesh("PLAYER_RIFLE_SKILL", "Player/Rifle/Skill/Skill", "Player", 26);
	AddMesh("PLAYER_RIFLE_WALK", "Player/Rifle/Walk/Walk", "Player", 21);

	AddMesh("ENEMY_01_IDLE", "monster1/Idle/Idle", "monster1", 61, true);
	AddMesh("ENEMY_01_WALK", "monster1/Walk/Walk", "monster1", 31, true);
	AddMesh("ENEMY_01_ATTACK", "monster1/att1/aAttack", "monster1", 26, true);

	AddMesh("ENEMY_02_IDLE", "monster2/Idle/Idle", "monster2", 41, true);
	AddMesh("ENEMY_02_WALK", "monster2/Walk/Walk", "monster2", 41, true);
	AddMesh("ENEMY_02_ATTACK", "monster2/att1/Attack", "monster2", 31, true);
	AddMesh("ENEMY_02_DEAD", "monster2/Dead/Dead", "monster2", 41, true);

	AddMesh("ENEMY_03_IDLE", "monster3/Idle/Idle", "monster3", 51, true);
	AddMesh("ENEMY_03_WALK", "monster3/Walk/Walk", "monster3", 36, true);
	AddMesh("ENEMY_03_ATTACK", "monster3/att1/Attack", "monster3", 36, true);
	AddMesh("ENEMY_03_DEAD", "monster3/Dead/Dead", "monster3", 44, true);

	AddMesh("BOSS_01_IDLE", "Boss/Idle/Idle", "Boss", 43, true);
	AddMesh("BOSS_01_WALK", "Boss/Walk/Walk", "Boss", 43, true);
	AddMesh("BOSS_01_ATTACK_01", "Boss/att1/Attack01", "Boss", 53, true);
	AddMesh("BOSS_01_ATTACK_02", "Boss/att2/Attack02", "Boss", 46, true);
	AddMesh("BOSS_01_SKILL", "Boss/Skill/Skill", "Boss", 83, true);
	AddMesh("BOSS_01_DEAD", "Boss/Dead/Dead", "Boss", 74, true);
	AddMesh("BOSS_01_BORN", "Boss/Born/Born", "Boss", 118, true);

	AddMesh("BOSS_02_IDLE", "Boss2/Idle/Idle", "Boss2", 36, true);
	AddMesh("BOSS_02_WALK", "Boss2/Walk/Walk", "Boss2", 33, true);
	AddMesh("BOSS_02_ATTACK_01", "Boss2/att1/Attack01", "Boss2", 53, true);
	AddMesh("BOSS_02_ATTACK_02", "Boss2/att2/Attack02", "Boss2", 146, true);
	AddMesh("BOSS_02_SKILL", "Boss2/Skill/Skill", "Boss2", 83, true);
	AddMesh("BOSS_02_DEAD", "Boss2/Dead/Dead", "Boss2", 74, true);
	AddMesh("BOSS_02_BORN", "Boss2/Born/Born", "Boss2", 118 , true);

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.AddScene("S_STAGE01", new CStage01());
	SCENE.AddScene("S_STAGECLEAR", new CStageClear());
	SCENE.AddScene("S_STAGE02", new CStage02());
	SCENE.AddScene("S_GAMECLEAR", new CGameClear());
	SCENE.AddScene("S_GAMEOVER", new CGameOver());
	SCENE.ChangeScene("S_STAGE01");

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
	CGameManager::ReleaseInstance();
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

void CMainGame::AddMesh(string _Key, string _Path, string _MapPath, int _Count,bool test)
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
		thread th = thread([=]() {
			for (int i = 0; i < _Count; i++)
			{
				if (test == false)
				{
					string Key = _Key + " (" + to_string(i + 1) + ")";
					string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
					string MapPath = "./resource/" + _MapPath + "/";
					GRAPHICS.AddMesh(Key, Path, MapPath);
				}
				else
				{
					if (i == 0)
					{
						string Key = _Key + " (" + to_string(i + 1) + ")";
						string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
						string MapPath = "./resource/" + _MapPath + "/";
						GRAPHICS.AddMesh(Key, Path, MapPath);
					}
					else
					{
						string Key = _Key + " (" + to_string(i + 1) + ")";
						string Key2 = _Key + " (" + to_string(1) + ")";
						string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
						string MapPath = "./resource/" + _MapPath + "/";
						GRAPHICS.m_mapMesh.insert(make_pair(Key, MESH(Key2)));
					}
				}


			}
		});
		th.join();

	}
}
