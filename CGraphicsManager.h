#pragma once
#include "CSingleton.h"
#include "CSprite.h"
#include "MeshLoader.h"


class CGraphicsManager :
	public CSingleton<CGraphicsManager>
{
public:
	CGraphicsManager();
	~CGraphicsManager();

private:
	LPD3DXSPRITE m_pSprite = NULL;
	LPD3DXFONT m_pFont = NULL;
	CSoundManager * m_pSoundManager = nullptr;

private:
	map<string, CSprite * > m_mapSprite;
	map<string, CMesh * > m_mapMesh;
	map<string, CSound *> m_mapSound;



public:
	CSprite * FindSprite(string _Key);
	CMesh * FindMesh(string _Key);

public:
	void  AddSprite( string _Key, string _Path);
	void  AddMesh(string _Key, string _Path,string _MapPath);
	CSound * AddSound(string _Key, wstring _Path);
public:
	void Play(string _Key, bool _bLoop);
	void dPlay(string _Key);
	void Stop(string _Key);

public:
	void Render_Font(string _Text, Matrix _matWorld,Color _Color, RenderMode _Mode);
	void Render_Sprite(CSprite * _pSprite, Matrix _matWorld, Vector2 _vCenter, Vector2 _vFillAmount, Color _Color,RenderMode _Mode);
	void Render_Mesh(CMesh * _pMesh, Matrix _matWorld, Color _Color);

	Matrix ToMatrix(Vector3 _vPos, Vector3  _vScale = Vector3(1, 1,1), Vector3 _vRotation = Vector3(0, 0, 0));
public:
	void OnLostDevice();
	void OnResetDevice();
};

#define GRAPHICS (*CGraphicsManager::GetInstance())
#define SPRITE GRAPHICS.FindSprite
#define MESH GRAPHICS.FindMesh