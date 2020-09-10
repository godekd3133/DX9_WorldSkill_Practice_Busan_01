#pragma once
#include "CSingleton.h"
class CInputManager
	: public CSingleton<CInputManager>
{
public:
	CInputManager();
	~CInputManager();

private:
	bool m_bCurInput[256];
	bool m_bLastInput[256];

public:
	void Update();
	Vector2 GetDeltaMousePos();
	Vector2 GetMousePos();
	bool KeyDown(int _Key);
	bool KeyPress(int _Key);
	bool KeyUp(int _Key);
};
#define INPUT (*CInputManager::GetInstance())

