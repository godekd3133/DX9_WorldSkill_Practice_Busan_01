#include "DXUT.h"
#include "CGraphicsManager.h"


CGraphicsManager::CGraphicsManager()
{
	D3DXCreateSprite(g_Device, &m_pSprite);
	D3DXCreateFont(g_Device, 80, 0, 0, 1, false, HANGUL_CHARSET, 0, 0, 0, L"¸¼Àº °íµñ Bold", &m_pFont);
}


CGraphicsManager::~CGraphicsManager()
{
	for (auto iter : m_mapSprite)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapSprite.clear();

	for (auto iter : m_mapMesh)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapMesh.clear();

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pFont);
}

CSprite * CGraphicsManager::FindSprite(string _Key)
{
	auto find = m_mapSprite.find(_Key);
	if (find != m_mapSprite.end())
	{
		return find->second;
	}
	return nullptr;
}

CMesh * CGraphicsManager::FindMesh(string _Key)
{
	/*auto find = m_mapMesh.find(_Key);
	if (find != m_mapMesh.end())
	{
		return find->second;
	}
	return nullptr;*/

	bool a = _Key == (*m_mapMesh.begin()).first;
	return m_mapMesh[_Key];
}

void CGraphicsManager::AddSprite(string _Key, string _Path)
{
	if (FindSprite(_Key)) return;

	string Key = _Key;
	string Path =  _Path;
	
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO info;
	if (S_OK == D3DXCreateTextureFromFileExA(
		g_Device,
		_Path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		nullptr,
		&pTexture

	))
	{
		CSprite * pSprite = new CSprite(pTexture, info);
		m_mapSprite.insert(make_pair(Key, pSprite));
	}
}

void CGraphicsManager::AddMesh(string _Key, string _Path, string _MapPath)
{
		CMeshLoader * pLoader = new CMeshLoader();
		wstring wPath;
		wPath.assign(_Path.begin(), _Path.end());
		pLoader->Create(g_Device, wPath.c_str(), _MapPath);

		if (pLoader->GetMesh() != nullptr)
		{
			CMesh * pMesh = new CMesh();
			pMesh->m_pMesh = pLoader->GetMesh();
			for (int i = 0; i < pLoader->GetNumMaterials(); i++)
			{
				pMesh->m_vecMaterial.push_back(pLoader->GetMaterial(i));
			}
			m_mapMesh.insert(make_pair(_Key, pMesh));
			SAFE_DELETE(pLoader);
		}
		SAFE_DELETE(pLoader);
}

void CGraphicsManager::Render_Font(string _Text, Matrix _matWorld, Color _Color, RenderMode _Mode)
{
	if (_Mode == RenderMode::RM_Billboard)
	{
		m_pSprite->SetWorldViewLH(nullptr, &CAMERA.m_matView);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_BILLBOARD);
		g_Device->SetRenderState(D3DRS_ZENABLE, false);
	}
	else if (_Mode == RenderMode::RM_Default)
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	else if (_Mode == RenderMode::RM_UI)
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&_matWorld);
	m_pFont->DrawTextA(m_pSprite, _Text.c_str(), _Text.size(), NULL, DT_CENTER | DT_NOCLIP, _Color);
	m_pSprite->End();
	g_Device->SetRenderState(D3DRS_ZENABLE, true);
}

void CGraphicsManager::Render_Sprite(CSprite * _pSprite, Matrix _matWorld, Vector2 _vCenter, Vector2 _vFillAmount, Color _Color, RenderMode _Mode)
{
	_pSprite->m_vAnchor = _vCenter;
	if (_Mode == RenderMode::RM_UI)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else if (_Mode == RenderMode::RM_Default)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	}
	else if (_Mode == RenderMode::RM_Billboard)
	{
		m_pSprite->SetWorldViewLH(nullptr, &CAMERA.m_matView);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_BILLBOARD | D3DXSPRITE_OBJECTSPACE); 
		g_Device->SetRenderState(D3DRS_ZENABLE, false);
	}

	m_pSprite->SetTransform(&_matWorld);

	RECT re = { 0, 0, _pSprite->GetWidth() * _vFillAmount.x, _pSprite->GetHeight() * _vFillAmount.y };
	Vector3 Center = Vector3(_pSprite->GetWidth() * _pSprite->m_vAnchor.x, _pSprite->GetHeight() * _pSprite->m_vAnchor.y, 0.f);
	m_pSprite->Draw(_pSprite->m_pTexture, &re, &Center, nullptr, _Color);

	m_pSprite->End();
	m_pSprite->SetWorldViewLH(nullptr, nullptr);
	g_Device->SetRenderState(D3DRS_ZENABLE, true);
}

void CGraphicsManager::Render_Mesh(CMesh * _pMesh, Matrix _matWorld, Color _Color)
{
	if (_pMesh)
	{
		g_Device->SetTransform(D3DTS_WORLD, &_matWorld);

		for (int i = 0; i < _pMesh->m_vecMaterial.size(); i++)
		{
			_pMesh->m_vecMaterial[i]->material.Emissive = D3DXCOLOR(_Color);
			g_Device->SetMaterial(&_pMesh->m_vecMaterial[i]->material);
			g_Device->SetTexture(0, _pMesh->m_vecMaterial[i]->pTexture);
			_pMesh->m_pMesh->DrawSubset(i);
		}


		Matrix iden;
		D3DXMatrixIdentity(&iden);
		g_Device->SetTransform(D3DTS_WORLD, &iden);
	}
}

void CGraphicsManager::OnLostDevice()
{
	m_pFont->OnLostDevice();
	m_pSprite->OnLostDevice();
}

void CGraphicsManager::OnResetDevice()
{
	m_pFont->OnResetDevice();
	m_pSprite->OnResetDevice();
}
