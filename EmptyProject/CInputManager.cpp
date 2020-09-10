#include "DXUT.h"
#include "CInputManager.h"


CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

void CInputManager::Update()
{
	memcpy(m_bLastInput, m_bCurInput, sizeof(m_bCurInput));

	for (int i = 0; i < 256; i++)
	{
		m_bCurInput[i] = GetAsyncKeyState(i);
	}
}

bool CInputManager::KeyDown(int _Key)
{
	return m_bCurInput[_Key] && m_bLastInput[_Key]== false;
}

bool CInputManager::KeyPress(int _Key)
{
	return m_bCurInput[256] && m_bLastInput[256];
}

bool CInputManager::KeyUp(int _Key)
{
	return m_bCurInput[_Key] == false && m_bLastInput[_Key];
}
