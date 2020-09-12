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
	float m_fFireDelay[2] = { 0.25f, 0.025f };
private:
};

#define GAME (*CGameManager::GetInstance())