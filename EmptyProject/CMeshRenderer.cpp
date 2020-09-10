#include "DXUT.h"
#include "CMeshRenderer.h"


CMeshRenderer::CMeshRenderer()
{
}


CMeshRenderer::~CMeshRenderer()
{
}

void CMeshRenderer::Awake()
{
}

void CMeshRenderer::Start()
{
}

void CMeshRenderer::Update()
{
}

void CMeshRenderer::LateUpdate()
{
}

void CMeshRenderer::OnRender()
{
}

void CMeshRenderer::OnDestroy()
{
}

void CMeshRenderer::OnCollision()
{
}

void CMeshRenderer::Init(CMesh * _pMesh, Color _Color)
{
	m_pMesh = _pMesh;
	m_Color = _Color;
}
