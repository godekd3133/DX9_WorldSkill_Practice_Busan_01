#include "DXUT.h"
#include "CSpriteRenderer.h"


CSpriteRenderer::CSpriteRenderer()
{
}


CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::Awake()
{
}

void CSpriteRenderer::Start()
{
}

void CSpriteRenderer::Update()
{
}

void CSpriteRenderer::LateUpdate()
{
}

void CSpriteRenderer::OnRender()
{
}

void CSpriteRenderer::OnDestroy()
{
}

void CSpriteRenderer::OnCollision()
{
}

void CSpriteRenderer::Init(CSprite * _pSprite, SortingLayer _SortingLayer, RenderMode _RenderMode, Color _Color)
{
	m_pSprite = _pSprite;
	m_SortingLayer = _SortingLayer;
	m_RenderMode = _RenderMode;
	m_Color = _Color;
}
