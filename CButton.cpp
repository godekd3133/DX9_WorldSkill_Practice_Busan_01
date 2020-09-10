#include "DXUT.h"
#include "CButton.h"


CButton::CButton()
{
}


CButton::~CButton()
{
}

void CButton::Awake()
{
}

void CButton::Start()
{
}

void CButton::Update()
{
	Vector2 vCursorPos = INPUT.GetMousePos();
	POINT ptMouse = { (INT)vCursorPos.x, (INT)vCursorPos.y };

	if (PtInRect(&m_reRect, ptMouse))
	{
		if (INPUT.KeyDown(VK_LBUTTON))
		{
			m_OnClick();
		}

		tf->LerpScale(m_vStartScale * 1.5f, 4.f  *dt);
	}
	tf->LerpScale(m_vStartScale , 4.f * dt);
}

void CButton::LateUpdate()
{
}

void CButton::OnDestroy()
{
}

void CButton::OnCollision(CGameObject * _pObject)
{
}

void CButton::Init(CSprite * _pSprite, Vector3 _vPos, Vector3 _vScale, function<void()> _OnClick)
{
	ac<CSpriteRenderer>()->Init(_pSprite, SortingLayer::SR_UI, RenderMode::RM_UI);
	tf->m_vPos = _vPos;
	tf->m_vScale = m_vStartScale = _vScale;

	m_OnClick = _OnClick;

	m_reRect = {
		(LONG)(tf->m_vPos.x - _pSprite->GetWidth() /2),
		(LONG)(tf->m_vPos.y - _pSprite->GetHeight() / 2),
		(LONG)(tf->m_vPos.x + _pSprite->GetWidth() / 2),
		(LONG)(tf->m_vPos.y + _pSprite->GetHeight() / 2)
	};
}
