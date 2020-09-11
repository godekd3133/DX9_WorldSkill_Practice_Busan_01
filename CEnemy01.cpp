#include "DXUT.h"
#include "CEnemy01.h"


CEnemy01::CEnemy01()
{
}


CEnemy01::~CEnemy01()
{
}

void CEnemy01::Awake()
{
}

void CEnemy01::Start()
{
}

void CEnemy01::Update()
{
}

void CEnemy01::LateUpdate()
{
}

void CEnemy01::OnDestroy()
{
}

void CEnemy01::OnCollision(CGameObject * _pObject)
{
}

void CEnemy01::Init(Vector3 _vPos)
{
	ac<CEnemy>()->Init(MESH("ENEMY_01_IDLE (1)"), 100, 1);

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.01, 0.01, 0.01);
}
