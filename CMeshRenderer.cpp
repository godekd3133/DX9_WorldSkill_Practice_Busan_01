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
	GRAPHICS.Render_Mesh(m_pMesh, go->tf->ToMatrix(), m_Color);
}

void CMeshRenderer::OnDestroy()
{
}

void CMeshRenderer::OnCollision(CGameObject * _pObject)
{
}

void CMeshRenderer::Init(CMesh * _pMesh, Color _Color)
{
	m_pMesh = _pMesh;
	m_Color = _Color;
}
