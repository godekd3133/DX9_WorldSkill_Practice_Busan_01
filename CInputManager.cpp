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

Vector2 CInputManager::GetDeltaMousePos()
{
	Vector2 vPos = GetMousePos() - Vector2(WINSIZEX / 2.f, WINSIZEY / 2.f);
	
	POINT ptCenter = { WINSIZEX / 2,WINSIZEY / 2 };
	ClientToScreen(DXUTGetHWND(), &ptCenter);
	SetCursorPos(ptCenter.x, ptCenter.y);
	


	return vPos;
}

Vector2 CInputManager::GetMousePos()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(DXUTGetHWND(), &ptMouse);


	return Vector2(ptMouse.x, ptMouse.y);
}

bool CInputManager::KeyDown(int _Key)
{
	return m_bCurInput[_Key] && m_bLastInput[_Key] == false;
}

bool CInputManager::KeyPress(int _Key)
{
	return m_bCurInput[_Key] && m_bLastInput[_Key];
}

bool CInputManager::KeyUp(int _Key)
{
	return m_bCurInput[_Key] == false && m_bLastInput[_Key];
}
