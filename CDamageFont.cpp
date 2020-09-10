#include "DXUT.h"
#include "CDamageFont.h"


CDamageFont::CDamageFont()
{
}


CDamageFont::~CDamageFont()
{
}

void CDamageFont::Awake()
{
}

void CDamageFont::Start()
{
}

void CDamageFont::Update()
{
	for (int i = 0; i < m_vecFontObject.size(); i++)
	{
		m_vecFontObject[i]->tf->m_vScale = tf->m_vScale;
		m_vecFontObject[i]->tf->m_vScale.y = -m_vecFontObject[i]->tf->m_vScale.y;

	}
	SetTransform();
}

void CDamageFont::LateUpdate()
{
}

void CDamageFont::OnDestroy()
{
	for (auto iter : m_vecFontObject)
		iter->Destroy();
}

void CDamageFont::OnCollision(CGameObject * _pObject)
{
}

void CDamageFont::Init(string _Key, Vector3 _vPos, int _Damage)
{
	string strDamage = to_string(_Damage);
	tf->m_vPos = _vPos;

	for (int i = 0; i < strDamage.size(); i++)
	{
		CGameObject * pFontObject = OBJ.Create();
		pFontObject->ac<CSpriteRenderer>()->Init(
			SPRITE(_Key + " (" + to_string(strDamage[i] - '0' + 1) + ")"),
			SortingLayer::SR_UI,
			RenderMode::RM_Billboard
		);
		m_vecFontObject.push_back(pFontObject);
	}


	m_vSize = Vector2(SPRITE(_Key + " (1)")->m_Info.Width, SPRITE(_Key+" (1)")->m_Info.Height);
	for (int i = 0; i < m_vecFontObject.size(); i++)
	{
		m_vecFontObject[i]->tf->m_vPos = tf->m_vPos;
		m_vecFontObject[i]->tf->m_vScale = tf->m_vScale;
		m_vecFontObject[i]->tf->m_vScale.y = -m_vecFontObject[i]->tf->m_vScale.y;
	}

	Vector3 Scale = tf->m_vScale;
	sa->Add(
		[=]()->bool {
		tf->m_vScale = Lerp(tf->m_vScale, Scale*2, dt *24);
		return true; 
	}, 0.25f
	);
	sa->Add(
		[=]()->bool {
		tf->m_vScale = Lerp(tf->m_vScale, Scale, dt * 24);
		return true;
	}, 0.25f
	);
	sa->Delay(0.33f);
	sa->Add(
		[=]()->bool {
		for (auto iter : m_vecFontObject)
		{
			iter->gc<CSpriteRenderer>()->m_Color = Lerp(iter->gc<CSpriteRenderer>()->m_Color, Color(1, 1, 1, 0), dt * 24);
		}
		return true;
	}, 0.1f
	);
	sa->Add(
		[=]()->bool {
		
		go->Destroy();
		return false;
	}
	);
}

void CDamageFont::InitCombo(string _Key, Vector3 _vPos, int _Combo)
{
	string strDamage = to_string(_Combo);
	tf->m_vPos = _vPos;

	for (int i = 0; i < strDamage.size(); i++)
	{
		CGameObject * pFontObject = OBJ.Create();
		pFontObject->ac<CSpriteRenderer>()->Init(
			SPRITE(_Key + " (" + to_string(strDamage[i] - '0' + 1) + ")"),
			SortingLayer::SR_UI,
			RenderMode::RM_UI
		);
		m_vecFontObject.push_back(pFontObject);
	}

	tf->m_vScale = Vector3(3,-3,3);

	m_vSize = Vector2(SPRITE(_Key + " (1)")->m_Info.Width, SPRITE(_Key + " (1)")->m_Info.Height);
	for (int i = 0; i < m_vecFontObject.size(); i++)
	{
		m_vecFontObject[i]->tf->m_vPos = tf->m_vPos;
		m_vecFontObject[i]->tf->m_vScale = tf->m_vScale;
		m_vecFontObject[i]->tf->m_vScale.y = -m_vecFontObject[i]->tf->m_vScale.y;
	}

	Vector3 Scale = tf->m_vScale;
	sa->Add(
		[=]()->bool {
		tf->m_vScale = Lerp(tf->m_vScale, Vector3(1,-1,1) , dt * 24);
		return true;
	}, 0.25f
	);
	
	sa->Delay(0.5f);
	sa->Add(
		[=]()->bool {
		for (auto iter : m_vecFontObject)
		{
			iter->gc<CSpriteRenderer>()->m_Color = Lerp(iter->gc<CSpriteRenderer>()->m_Color, Color(1, 1, 1, 0), dt * 24);
		}
		return true;
	}, 0.1f
	);
	sa->Add(
		[=]()->bool {

		go->Destroy();
		return false;
	}
	);
}

void CDamageFont::SetAlpha(float _Alpha)
{
	for (int i = 0; i < m_vecFontObject.size() ; i++)
	{
		m_vecFontObject[i]->gc<CSpriteRenderer>()->m_Color = Color(1, 1, 1,_Alpha);
	}
}

float CDamageFont::GetAlpha()
{
	return m_vecFontObject[0]->gc<CSpriteRenderer>()->m_Color.a;
}

void CDamageFont::SetTransform()
{
	int half = m_vecFontObject.size()/2;
	for (int i = 0; i <= m_vecFontObject.size()/2; i++)
	{
		if(half +i  < m_vecFontObject.size())
		m_vecFontObject[half +i]->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f - (float)i, 0.5f);
		if (half -i >= 0)
			m_vecFontObject[half -i]->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + (float)i, 0.5f);
	}
}
