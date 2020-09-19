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
	//GRAPHICS.AddSound("BG", L"./resource/2.5Stage.wav");
	//GRAPHICS.Play("BG", true);
	AddMesh("MAP_STAGE01", "map/1-1stage/1stage_reamke", "map/1-1stage");//21);
	AddSprite("MAP_STAGE01_MINIMAP", "map/1-1stage/mapnormal");

	AddMesh("MAP_STAGE02_PART01", "map/2-1stage/2stageRemake1", "map/2-1stage");//21);
	AddMesh("MAP_STAGE02_PART02", "map/2-1stage/2stageRemake2", "map/2-1stage");//21);
	AddMesh("MAP_STAGE02_PART03", "map/2-1stage/2stageRemake3", "map/2-1stage");//21);

	AddMesh("PLAYER_BULLET", "bullet", "");
	AddSprite("BULLET_MAPPING_01", "Bullet1");
	AddSprite("BULLET_MAPPING_02", "Bullet2");

	AddMesh("OBSTACLE_MINE", "Obstacle/mineland/mine", "Obstacle/mineland");
	AddMesh("OBSTACLE_TRAP", "Obstacle/Trap/Trap", "Obstacle/Trap");
	AddMesh("OBSTACLE_THOM", "Obstacle/Thorn/model", "Obstacle/Thorn");
AddSprite("UI_ENEMY_DAMAGEFONT", "UI/damagefont2/Damage", 10);//21);

	AddSprite("EFFECT_EXPLOSION", "Effect/Explosion/Explosion", 8);//21);
	AddSprite("EFFECT_ENEMY_DEAD", "Effect/EnemyDead/EnemyDead", 23);//21);
	AddSprite("EFFECT_PLAYER_SKILL_02", "Effect/PlayerSkill02/PlayerSkill02_2", 16);//21);

	AddSprite("UI_ICON_PISTOL", "UI/PlayerStatus_Weapon_Pistol");
	AddSprite("UI_ICON_RIFLE", "UI/PlayerStatus_Weapon_Rifle");
	
	AddSprite("UI_BULLET_SLASH", "UI/gunGauge2");

	AddSprite("UI_MINIMAP_STAGE01", "UI/Minimap_Stage01");
	AddSprite("UI_MINIMAP_STAGE02", "UI/Minimap_Stage02");

	AddSprite("UI_MINIMAP_PLAYER", "UI/Minimap_Player");
	AddSprite("UI_MINIMAP_ENEMY", "UI/Minimap_Enemy");
	AddSprite("UI_PLAYERSTATUS_01", "UI/PlayerStatus_01");
	AddSprite("UI_PLAYERSTATUS_03", "UI/PlayerStatus_03");
	AddSprite("UI_PLAYERSTATUS_HPBAR", "UI/hp_bar");
	AddSprite("UI_PLAYERSTATUS_HPBAR_YELLOW", "UI/hp_bar_Yellow");
	AddSprite("UI_PLAYERSTATUS_HPBAR_BG", "UI/HpBarBackground");
	AddSprite("UI_PLAYERSTATUS_EXPBAR", "UI/exp_bar");
	AddSprite("UI_PLAYERSTATUS_EXPBAR_BG", "UI/ExpBarBackground");

	AddSprite("UI_BOSSHPBAR_BG", "UI/boss_hp_ui_2");
	AddSprite("UI_BOSSHPBAR", "UI/boss_hp_bar");
	AddSprite("UI_BOSSHPBAR_YELLOW", "UI/boss_hp_bar_Yelllow");
	AddSprite("UI_BOSS_HPICON", "UI/boss_hp_ui_1");

	AddSprite("UI_HPBAR_BG", "UI/hp_ui_1");
	AddSprite("UI_HPBAR", "UI/enemy_hpbar");
	AddSprite("UI_HPBAR_YELLOW", "UI/enemy_hpbar_yellow");
	AddSprite("UI_MONSTER_HPICON", "UI/enemy_hp");
	AddSprite("UI_SHADOW", "UI/Shadow");

	AddSprite("UI_TIME", "UI/time");

	AddSprite("UI_SKILL_COOLTIME", "skillcolldown");
	AddSprite("UI_SKILL_BACKGROUND", "skillPreset");
	AddSprite("UI_SKILL_01", "miss");
	AddSprite("UI_SKILL_02", "shotdown");
	AddSprite("UI_SKILL_03", "antibiotic");
	AddSprite("UI_SKILL_04", "vaccin");


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

	AddMesh("ENEMY_02_IDLE", "monster2/Idle/Idle", "monster2", 61, true);
	AddMesh("ENEMY_02_WALK", "monster2/Walk/Walk", "monster2", 25, true);
	AddMesh("ENEMY_02_ATTACK_01", "monster2/att1/Attack01", "monster2", 41);
	AddMesh("ENEMY_02_ATTACK_02", "monster2/att2/Attack02", "monster2", 38);
	AddMesh("ENEMY_02_DEAD", "monster2/Dead/Dead", "monster2", 36, true);

	AddMesh("ENEMY_03_IDLE", "monster3/Idle/Idle", "monster3", 51, true);
	AddMesh("ENEMY_03_WALK", "monster3/Walk/Walk", "monster3", 36, true);
	AddMesh("ENEMY_03_ATTACK", "monster3/att1/Attack", "monster3",36);
	AddMesh("ENEMY_03_DEAD", "monster3/Dead/Dead", "monster3", 44, true);

	AddMesh("BOSS_01_IDLE", "Boss/Idle/Idle", "Boss", 43, true);
	AddMesh("BOSS_01_WALK", "Boss/Walk/Walk", "Boss", 43, true);
	AddMesh("BOSS_01_ATTACK_01", "Boss/att1/Attack01", "Boss", 53, true);
	AddMesh("BOSS_01_ATTACK_02", "Boss/att2/Attack02", "Boss", 46,true);
	AddMesh("BOSS_01_SKILL", "Boss/Skill/Skill", "Boss", 83, true);
	AddMesh("BOSS_01_DEAD", "Boss/Dead/Dead", "Bo ss", 74, true);
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
					//else
					//{
					//	string Key = _Key + " (" + to_string(i + 1) + ")";
					//	string Key2 = _Key + " (" + to_string(1) + ")";
					//	string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
					//	string MapPath = "./resource/" + _MapPath + "/";
					//	GRAPHICS.m_mapMesh.insert(make_pair(Key, MESH(Key2)));
					//}
				}


			}


	}
}
