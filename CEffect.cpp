#include "DXUT.h"
#include "CEffect.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

void CEffect::Awake()
{
}

void CEffect::Start()
{
}

void CEffect::Update()
{
	if (gc<CAnimator2D>()->GetCurrentState()->GetNormalizeTime() >= 0.9f)
	{
		go->Destroy();
	}
}

void CEffect::LateUpdate()
{
}

void CEffect::OnDestroy()
{
}

void CEffect::OnCollision(CGameObject * _pObject)
{
}

void CEffect::Init(string _ResKey, float _Delay, Vector3 _vPos)
{
	ac<CSpriteRenderer>()->Init(nullptr, SortingLayer::SR_Effect, RenderMode::RM_Billboard);
	ac<CAnimator2D>()->AddState("EFFECT", _ResKey, _Delay,false);
	gc<CAnimator2D>()->SetCurrentState("EFFECT");
	tf->m_vPos = _vPos;

}
