#include "DXUT.h"
#include "CSprite.h"


CSprite::CSprite(LPDIRECT3DTEXTURE9 _pTexture, D3DXIMAGE_INFO _Info)
{
	m_pTexture = _pTexture;
	m_Info = _Info;

	m_vAnchor = Vector2(0.5f, 0.5f);
}

CSprite::~CSprite()
{
	SAFE_RELEASE(m_pTexture);
}
