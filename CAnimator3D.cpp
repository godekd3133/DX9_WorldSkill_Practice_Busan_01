#include "DXUT.h"
#include "CAnimator3D.h"


CAnimator3D::CAnimator3D()
{
	m_pCurrentState = nullptr;
}


CAnimator3D::~CAnimator3D()
{
	for (auto iter : m_mapAnimation)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapAnimation.clear();
}

void CAnimator3D::Awake()
{
}

void CAnimator3D::Start()
{
	MeshRenderer = gc<CMeshRenderer>();
}

void CAnimator3D::Update()
{
	if (m_pCurrentState)
	{
		if(m_pCurrentState->m_bEnable)
		m_pCurrentState->Update();
		MeshRenderer->m_pMesh = m_pCurrentState->GetCurrentMesh();
	}
}

void CAnimator3D::LateUpdate()
{
}

void CAnimator3D::OnDestroy()
{
}

void CAnimator3D::OnCollision()
{
}

void CAnimator3D::SetCurrentState(string _State)
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

CAnimation3D * CAnimator3D::GetState(string _State)
{
	return m_mapAnimation[_State];
}

CAnimation3D * CAnimator3D::GetCurrentState()
{
	return m_pCurrentState;
}

void CAnimator3D::AddState(string _StateName, string _ResourceKey, float _Delay, bool _Repeat)
{
	CAnimation3D * pAnimation = new CAnimation3D();

	pAnimation->m_Name = _StateName;
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

		CMesh * pFrameMesh = MESH(Key);

		if (pFrameMesh == nullptr)
		{
			pAnimation->m_iMaxFrame = Frame - 1;
			break;
		}
		pAnimation->m_vecMesh.push_back(pFrameMesh);

		Frame++;
	}
	m_mapAnimation.insert(make_pair(_StateName, pAnimation));
}
