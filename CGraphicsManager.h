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

private:
	map<string, CSprite * > m_mapSprite;
	map<string, CMesh * > m_mapMesh;

public:
	CSprite * FindSprite(string _Key);
	CMesh * FindMesh(string _Key);

public:
	void  AddSprite( string _Key, string _Path);
	void  AddMesh(string _Key, string _Path,string _MapPath);

public:
	void Render_Font(string _Text, Matrix _matWorld,Color _Color, RenderMode _Mode);
	void Render_Sprite(CSprite * _pSprite, Matrix _matWorld, Vector2 _vCenter, Vector2 _vFillAmount, Color _Color,RenderMode _Mode);
	void Render_Mesh(CMesh * _pMesh, Matrix _matWorld, Color _Color);

public:
	void OnLostDevice();
	void OnResetDevice();
};

#define GRAPHICS (*CGraphicsManager::GetInstance())
#define SPRITE GRAPHICS.FindSprite
#define MESH GRAPHICS.FindMesh