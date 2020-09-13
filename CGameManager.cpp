#include "DXUT.h"
#include "CGameManager.h"


CGameManager::CGameManager()
{
	Reset();
}


CGameManager::~CGameManager()
{
}

void CGameManager::Reset()
{
	m_fFireTime[0] = 0.f;
	m_fFireTime[1] = 0.f;

	m_fFireDelay[0] = 0.25f;
	m_fFireDelay[1] = 0.1f;

	m_iBulletDamage[0] = 120;
	m_iBulletDamage[1] = 70;

	m_iCurrentBullet[0] = 6;
	m_iCurrentBullet[1] = 0;

	m_iHavingBullet[0] = 0;
	m_iHavingBullet[1] = 500;

	m_iMaxBullet[0] = 6;
	m_iMaxBullet[1] = 30;
	
	for (int i = 0; i < 4; i++)
		m_fSkillTime[i] = 0.f;

	Level = 1;
	
	Timer = 0.f;

	CurHp = 100;
	MaxHp = 100;

	CurExp = 0;
	MaxExp = 1000;

}
