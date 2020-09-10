#include "DXUT.h"
#include "CAnimator2D.h"


CAnimator2D::CAnimator2D()
{
	m_pCurrentState = nullptr;
}


CAnimator2D::~CAnimator2D()
{
	for (auto iter : m_mapAnimation)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapAnimation.clear();
}

void CAnimator2D::Awake()
{
}

void CAnimator2D::Start()
{
	SpriteRenderer = gc<CSpriteRenderer>();
}

void CAnimator2D::Update()
{
	if (m_pCurrentState)
	{
		if (m_pCurrentState->m_bEnable)
			m_pCurrentState->Update();
		SpriteRenderer->m_pSprite = m_pCurrentState->GetCurrentSprite();
	}
}

void CAnimator2D::LateUpdate()
{
}

void CAnimator2D::OnDestroy()
{
}

void CAnimator2D::OnCollision(CGameObject * _pObject)
{
}

void CAnimator2D::SetCurrentState(string _State)
{
	if (m_pCurrentState != m_mapAnimation[_State])
	{
		m_pCurrentState = m_mapAnimation[_State];
		m_pCurrentState->m_bEnable = true;
		m_pCurrentState->m_iCurFrame = 0;
	}
	else
		m_pCurrentState = m_mapAnimation[_State];
}

CAnimation2D * CAnimator2D::GetState(string _State)
{
	return nullptr;
}

CAnimation2D * CAnimator2D::GetCurrentState()
{
	return m_pCurrentState;
}

void CAnimator2D::AddState(string _StateName, string _ResourceKey, float _Delay, bool _Repeat)
{
	CAnimation2D * pAnimation = new CAnimation2D();

	pAnimation->m_fTime = 0.f;
	pAnimation->m_fDelay = _Delay;
	pAnimation->m_bRepeat = _Repeat;
	pAnimation->m_bEnable = true;
	pAnimation->m_iCurFrame = 0;
	pAnimation->m_iMaxFrame = 0;

	int Frame = 1;

	while (1)
	{
		string Key = _ResourceKey + " (" + to_string(Frame) + ")";

		CSprite * pFrameSprite = SPRITE(Key);

		if (pFrameSprite == nullptr)
		{
			pAnimation->m_iMaxFrame = Frame - 1;
			break;
		}
			pAnimation->m_vecSprite.push_back(pFrameSprite);

		Frame++;
	}
	m_mapAnimation.insert(make_pair(_StateName, pAnimation));
}
