#include "DXUT.h"
#include "CObstacle.h"

CObstacle::CObstacle()
{
}

CObstacle::~CObstacle()
{
}

void CObstacle::Awake()
{
}

void CObstacle::Start()
{
}

void CObstacle::Update()
{
}

void CObstacle::LateUpdate()
{
}

void CObstacle::OnDestroy()
{
}

void CObstacle::OnCollision(CGameObject * _pObject)
{
}

void CObstacle::Init(ObstacleType _Type, Vector3 _vPos)
{
	m_Type = _Type;
	tf->m_vPos = _vPos;
	ac<CCollider>()->Init(1.f);
	if (m_Type == ObstacleType::Mine)
	{
		ac<CMeshRenderer>()->Init(MESH("OBSTACLE_MINE"));
	}
	else	if (m_Type == ObstacleType::Thom)
	{
		ac<CMeshRenderer>()->Init(MESH("OBSTACLE_THOM"), Color(1,0,0,1));
	}
	else 	if (m_Type == ObstacleType::Trap)
	{
		ac<CMeshRenderer>()->Init(MESH("OBSTACLE_TRAP"));
	}
}
