#include "DXUT.h"
#include "CGraphicsManager.h"


CGraphicsManager::CGraphicsManager()
{
	D3DXCreateSprite(g_Device, &m_pSprite);
	D3DXCreateFont(g_Device, 80, 0, 0, 1, false, HANGUL_CHARSET, 0, 0, 0, L"Noto Sans KR Bold", &m_pFont);
	m_pSoundManager = new CSoundManager();
	m_pSoundManager->Initialize(DXUTGetHWND(), 2);
}


CGraphicsManager::~CGraphicsManager()
{
	for (auto iter : m_mapSprite)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapSprite.clear();
	for (auto iter : m_mapSound)
	{
		iter.second->Stop();
		iter.second->Reset();
		SAFE_DELETE(iter.second);
	}
	m_mapSound.clear();

	SAFE_DELETE(m_pSoundManager);

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
	auto find = m_mapMesh.find(_Key);
	if (find != m_mapMesh.end())
	{
		return find->second;
	}
	return nullptr;
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
		D3DFMT_A8B8G8R8,
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
	if (FindMesh(_Key))
	{
		m_mapMesh.insert(make_pair(_Key, FindMesh(_Key)));
		return;
	}		
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

CSound * CGraphicsManager::AddSound(string _Key, wstring _Path)
{
	CSound * pSound = nullptr;
	m_pSoundManager->Create(&pSound, (LPWSTR)_Path.c_str());
	if (pSound != nullptr)
	{
		m_mapSound.insert(make_pair(_Key, pSound));
		return pSound;
	}
	return nullptr;
}

void CGraphicsManager::Play(string _Key, bool _bLoop)
{
	if (m_mapSound[_Key]->IsSoundPlaying() == false)
		m_mapSound[_Key]->Play(0, _bLoop);
}

void CGraphicsManager::dPlay(string _Key)
{
	LPDIRECTSOUNDBUFFER buf;

	m_pSoundManager->GetDirectSound()->DuplicateSoundBuffer(m_mapSound[_Key]->GetBuffer(0), &buf);

	buf->SetCurrentPosition(0);

	buf->Play(0, 0, 0);
}

void CGraphicsManager::Stop(string _Key)
{
	if (m_mapSound[_Key]->IsSoundPlaying())
		m_mapSound[_Key]->Stop();
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
	m_pFont->DrawTextA(m_pSprite, _Text.c_str(), _Text.size(), NULL, DT_CENTER | DT_NOCLIP , _Color);
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
	else if (_Mode == RenderMode::RM_BillboardNonUI)
	{
		m_pSprite->SetWorldViewLH(nullptr, &CAMERA.m_matView);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_BILLBOARD | D3DXSPRITE_OBJECTSPACE);
	}

	m_pSprite->SetTransform(&_matWorld);

	RECT re = { 0, 0, _pSprite->GetWidth() * _vFillAmount.x, _pSprite->GetHeight() * _vFillAmount.y };
	Vector3 Center = Vector3(_pSprite->GetWidth() * _pSprite->m_vAnchor.x, _pSprite->GetHeight() * _pSprite->m_vAnchor.y, 0.f);
	m_pSprite->Draw(_pSprite->m_pTexture, &re, &Center, nullptr, _Color);

	m_pSprite->End();
	m_pSprite->SetWorldViewLH(nullptr, nullptr);
	g_Device->SetRenderState(D3DRS_ZENABLE, true);
}

//void CGraphicsManager::Render_Mesh(CMesh * _pMesh, Matrix _matWorld, Color _Color)
//{
//	if (_pMesh)
//	{
//		g_Device->SetTransform(D3DTS_WORLD, &_matWorld);
//
//		for (int i = 0; i < _pMesh->m_vecMaterial.size(); i++)
//		{
//			_pMesh->m_vecMaterial[i]->material.Emissive = D3DXCOLOR(_Color);
//
//			g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true); 
//			g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//			g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//			g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
//			g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//			g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
//
//		
//			g_Device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DXCOLOR(_Color));
//
//			g_Device->SetMaterial(&_pMesh->m_vecMaterial[i]->material);
//			g_Device->SetTexture(0, _pMesh->m_vecMaterial[i]->pTexture);
//			_pMesh->m_pMesh->DrawSubset(i);
//		}
//		Matrix iden;
//		D3DXMatrixIdentity(&iden);
//		g_Device->SetTransform(D3DTS_WORLD, &iden);
//		g_Device->SetTexture(0, nullptr);
//	}
//}

void CGraphicsManager::Render_Mesh(CMesh * _pMesh, Matrix _matWorld, Color _Color, CSprite * _pOverride)
{
	if (_pMesh)
	{
		g_Device->SetTransform(D3DTS_WORLD, &_matWorld);

		for (int i = 0; i < _pMesh->m_vecMaterial.size(); i++)
		{
			//LPDIRECT3DTEXTURE9  a = _pMesh->m_vecMaterial[i]->pTexture;
			//_pMesh->m_vecMaterial[i]->pTexture = _pOverride->m_pTexture;
			_pMesh->m_vecMaterial[i]->material.Emissive = D3DXCOLOR(_Color);
			
			g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			
			g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
			
			
			g_Device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DXCOLOR(_Color));
			
			g_Device->SetMaterial(&_pMesh->m_vecMaterial[i]->material);
			if (_pOverride != nullptr)
				g_Device->SetTexture(0, _pOverride->m_pTexture);
			else
				g_Device->SetTexture(0, _pMesh->m_vecMaterial[i]->pTexture);

			_pMesh->m_pMesh->DrawSubset(i);
		}
		Matrix iden;
		D3DXMatrixIdentity(&iden);
		g_Device->SetTransform(D3DTS_WORLD, &iden);
//		g_Device->SetTexture(0, nullptr);
	}
}

Matrix CGraphicsManager::ToMatrix(Vector3 _vPos, Vector3 _vScale, Vector3 _vRotation)
{
	Matrix matTrans, matRotX, matRotY, matRotZ, matScale;

	D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, _vPos.z);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(_vRotation.x));

	D3DXMatrixRotationY(&matRotY, D3DXToRadian(_vRotation.x));

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(_vRotation.x));

	D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, _vScale.z);

	return matScale * matRotX*matRotY * matRotZ * matTrans;
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
