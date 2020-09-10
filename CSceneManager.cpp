#include "DXUT.h"
#include "CSceneManager.h"


CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
	for (auto iter : m_mapScene)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_mapScene.clear();
}

void CSceneManager::AddScene(string _Key, CScene * _pScene)
{
	m_mapScene[_Key] = _pScene;
}

void CSceneManager::ChangeScene(string _Key)
{
	m_pNextScene = m_mapScene[_Key];
}

void CSceneManager::Update()
{
	if (m_pCurScene)
		m_pCurScene->Update();

	if (m_pNextScene)
	{
		if (m_pCurScene)
			m_pCurScene->Release();
		m_pNextScene->Init();

		m_pCurScene = m_pNextScene;
		m_pNextScene = nullptr;
	}
}

void CSceneManager::Render()
{
	if (m_pCurScene)
		m_pCurScene->Render();
}
