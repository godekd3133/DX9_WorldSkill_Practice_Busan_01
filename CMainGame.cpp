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
	D3DLIGHT9 light;                 // Direct3D 9 조명 구조체 변수 선언

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_POINT;    // 조명의 타입은 포인트 라이트로 설증


	light.Diffuse.r = 1.0f;               // 조명의 Red 색 설정

	light.Diffuse.g = 0.0f;              // 조명의 Green 색 설정

	light.Diffuse.b = 0.0f;              // 조명의 Blue 색 설정

	light.Attenuation0 = 0.000000001f;  // 광원으로부터 멀어질 때의 감쇄값 

	light.Range = 5000000.0f;         //  조명이 미치는 범위



	light.Position.x = -5.0;            // 조명의 위치하는 x 좌표

	light.Position.y = 0.0;             // 조명이 위치하는 y 좌표

	light.Position.z = 5.0;             // 조명이 위치하는 z 좌표

	g_Device->SetLight(1, &light);     // 라이트 번호 지정 (여기에서는 1번)

	g_Device->LightEnable(1, TRUE); // 1번 라이트 켜기



	// 라이트 사용 기능을 TRUE로 함. (이 기능을 끄면 모든 라이트 사용은 중지됨)

	g_Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 최종적으로 엠비언트 라이트 켜기 (환경광의 양을 결정)

	g_Device->SetRenderState(D3DRS_AMBIENT, 0x00202020);

	std::future<void> a =
		std::async(launch::async, [=]() {
		AddMesh("MAP_STAGE01", "map/1-1stage/1stage_reamke", "map/1-1stage");//21);
		AddSprite("MAP_STAGE01_MINIMAP", "map/1-1stage/mapnormal");

		AddMesh("PLAYER_BULLET", "bullet","");

		AddSprite("EFFECT_EXPLOSION", "Effect/Explosion/Explosion",8);//21);


		//AddMesh("MAP_STAGE02_1", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		//AddMesh("MAP_STAGE02_2", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		//AddMesh("MAP_STAGE02_3", "Map/2-1Stage/2stageRemake1", "Map/2-1Stage", 1);//21);
		//AddSprite("MAP_STAGE02_MINIMAP", "map/2-1stage/mapnormal");

		AddMesh("PLAYER_PISTOL_IDLE", "Player/Pistol/Idle/Idle", "Player", 1);//21);
		AddMesh("PLAYER_PISTOL_RUN", "Player/Pistol/Run/Run", "Player", 1);//21);
		AddMesh("PLAYER_PISTOL_SHOOT", "Player/Pistol/Shoot/Shoot", "Player", 1);//16);
		AddMesh("PLAYER_PISTOL_SKILL", "Player/Pistol/Skill/Skill", "Player", 1);//26);
		AddMesh("PLAYER_PISTOL_WALK", "Player/Pistol/Walk/Walk", "Player", 1);//21);
		AddMesh("PLAYER_RIFLE_IDLE", "Player/Rifle/Idle/Idle", "Player", 1);//21);
		AddMesh("PLAYER_RIFLE_RUN", "Player/Rifle/Run/Run", "Player", 1);//21);
		AddMesh("PLAYER_RIFLE_SHOOT", "Player/Rifle/Shoot/Shoot", "Player", 1);//16);
		AddMesh("PLAYER_RIFLE_SKILL", "Player/Rifle/Skill/Skill", "Player", 1);//26);
		AddMesh("PLAYER_RIFLE_WALK", "Player/Rifle/Walk/Walk", "Player", 1);//21);

		AddMesh("ENEMY_01_IDLE", "monster1/Idle/Idle", "monster1",					1);//61);
		AddMesh("ENEMY_01_WALK", "monster1/Walk/Walk", "monster1",					1);//31);
		AddMesh("ENEMY_01_ATTACK", "monster1/att1/Attack", "monster1",				1);//26);
		//
		//AddMesh("ENEMY_02_IDLE", "monster2/Idle/Idle", "monster2",					1);//41);
		//AddMesh("ENEMY_02_WALK", "monster2/Walk/Walk", "monster2",					1);//41);
		//AddMesh("ENEMY_02_ATTACK", "monster2/att1/Attack", "monster2",				1);//31);
		//AddMesh("ENEMY_02_DEAD", "monster2/Dead/Dead", "monster2",					1);//41);
		//
		//AddMesh("ENEMY_03_IDLE", "monster3/Idle/Idle", "monster3",					1);//51);
		//AddMesh("ENEMY_03_WALK", "monster3/Walk/Walk", "monster3",					1);//36);
		//AddMesh("ENEMY_03_ATTACK", "monster3/att1/Attack", "monster3",				1);//36);
		//AddMesh("ENEMY_03_DEAD", "monster3/Dead/Dead", "monster3",					1);//44);

		//AddMesh("BOSS_01_IDLE", "Boss/Idle/Idle", "Boss",							1);//43);
		//AddMesh("BOSS_01_WALK", "Boss/Walk/Walk", "Boss",							1);//43);
		//AddMesh("BOSS_01_ATTACK_01", "Boss/att1/Attack01", "Boss",					1);//53);
		//AddMesh("BOSS_01_ATTACK_02", "Boss/att2/Attack02", "Boss",					1);//46);
		//AddMesh("BOSS_01_SKILL", "Boss/Skill/Skill", "Boss",						1);//83);
		//AddMesh("BOSS_01_DEAD", "Boss/Dead/Dead", "Boss",							1);//74);
		//AddMesh("BOSS_01_BORN", "Boss/Born/Born", "Boss",							1);//118);
		//
		//AddMesh("BOSS_02_IDLE", "Boss2/Idle/Idle", "Boss2",							1);//36);
		//AddMesh("BOSS_02_WALK", "Boss2/Walk/Walk", "Boss2",							1);//33);
		//AddMesh("BOSS_02_ATTACK_01", "Boss2/att1/Attack01", "Boss2",				1);//53);
		//AddMesh("BOSS_02_ATTACK_02", "Boss2/att2/Attack02", "Boss2",				1);//146);
		//AddMesh("BOSS_02_SKILL", "Boss2/Skill/Skill", "Boss2",						1);//83);
		//AddMesh("BOSS_02_DEAD", "Boss2/Dead/Dead", "Boss2",							1);//74);
		//AddMesh("BOSS_02_BORN", "Boss2/Born/Born", "Boss2",							1);//118);
	});
	

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
