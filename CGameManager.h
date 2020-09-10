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

};

#define GAME (*CGameManager::GetInstance())