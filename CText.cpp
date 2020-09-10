#include "DXUT.h"
#include "CText.h"


CText::CText()
{
}


CText::~CText()
{
}

void CText::Awake()
{
}

void CText::Start()
{
}

void CText::Update()
{
}

void CText::LateUpdate()
{
}

void CText::OnRender()
{
	GRAPHICS.Render_Font(m_Text, tf->ToMatrix(), m_Color, m_RenderMode);
}

void CText::OnDestroy()
{
}

void CText::OnCollision()
{
}

void CText::Init(string _Text, SortingLayer _SortingLayer, RenderMode _RenderMode, Color _Color)
{
	m_Text = _Text;
	m_SortingLayer = _SortingLayer;
	m_RenderMode = _RenderMode;
	m_Color = _Color;
}
