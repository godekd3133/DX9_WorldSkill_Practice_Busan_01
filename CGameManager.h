#pragma once
#include "CSingleton.h"
struct UserInfo {
	string Name;
		int Score;
};
class CGameManager :
	public CSingleton< CGameManager>
{
public:
	CGameManager();
	~CGameManager();
	
public:
	CGameObject * m_pPlayer = nullptr;
	CStageMap * m_pMap = nullptr;

	float MoveSpeed = 6;

	float m_fFireTime[2] = { 0.f, 0.f };
	float m_fFireDelay[2] = { 0.25f, 0.1f };
	float m_iBulletDamage[2] = { 120,70 };
	int m_iCurrentBullet[2] = { 6,0 };
	int m_iHavingBullet[2] = { 0,500 };
	int m_iMaxBullet[2] = { 6,30 };

	float m_fSkillTime[4] = { 0,0,0,0 };
	float m_fSkillCoolTime[4] = { 4,8,12,16 };

	int Level;

	int CurHp = 400;
	int MaxHp;

	int CurExp;
	int MaxExp;
	float Timer;
	void Reset();
private:
};

#define GAME (*CGameManager::GetInstance())