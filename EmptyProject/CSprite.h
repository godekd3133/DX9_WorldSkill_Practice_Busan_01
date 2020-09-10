#pragma once
class CSprite
{
public:
	CSprite(LPDIRECT3DTEXTURE9 _pTexture, D3DXIMAGE_INFO _Info);
	~CSprite();

public:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;
	D3DXIMAGE_INFO m_Info;

	Vector2 m_vAnchor;
public:
	float GetWidth() { return m_Info.Width; }
	float GetHeight() { return m_Info.Height; }
};       

