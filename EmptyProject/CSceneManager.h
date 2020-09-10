#pragma once
#include "CSingleton.h"
#include "CScene.h"

class CSceneManager :
	public CSingleton< CSceneManager>
{
public:
	CSceneManager();
	~CSceneManager();

private:
	CScene * m_pCurScene = nullptr;
	CScene * m_pNextScene = nullptr;
	
private:
	map <string, CScene *> m_mapScene;

public:
	void AddScene(string _Key, CScene * _pScene);
	void ChangeScene(string _Key);

	void Update();
	void Render();
};


#define SCENE (*CSceneManager::GetInstance())