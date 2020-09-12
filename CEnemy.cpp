#include "DXUT.h"
#include "CEnemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Awake()
{
}

void CEnemy::Start()
{
}

void CEnemy::Update()
{
	if(m_bIsDead == false)
	if (m_bVaccine)
	{
		list<CGameObject*> listEnemy = OBJ.Finds(Tag::Enemy);

		listEnemy.remove(go);

		if (listEnemy.empty() == false)
		{
			OBJ.SortByDistance(listEnemy);

			if (GetLength(tf->m_vPos,listEnemy.front()->tf->m_vPos) < m_fFindRange)
			{
				m_pTarget = listEnemy.front();
			}
		}
		else
		{
			m_pTarget = nullptr;
		}
	}
	else
	{
		if (GetLength(tf->m_vPos, GAME.m_pPlayer->tf->m_vPos) < m_fFindRange)
		{
			m_pTarget = GAME.m_pPlayer;
		}
		else
		{
			m_pTarget = nullptr;
		}
	}

}

void CEnemy::LateUpdate()
{

}


void CEnemy::OnDestroy()
{
	
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
	
}

void CEnemy::Init(CMesh * _pMesh, int _Hp, int _Size, float _FindRange, float _AttackRange, float _MoveSpeed)
{
	go->m_Tag = Tag::Enemy;
	ac<CMeshRenderer>()->Init(_pMesh);
	ac<CCollider>()->Init(_Size);

	m_iCurHp = _Hp;
	m_iMaxHp = _Hp;

	m_fAttackRange = _AttackRange;
	m_fFindRange = _FindRange;
	m_fMoveSpeed = _MoveSpeed;

	m_bIsDead = false;
	m_bVaccine = false;
}

void CEnemy::Hit(int _Damage)
{
	if (m_bIsDead == false)
	{
		m_iCurHp -= _Damage;
		if (m_iCurHp <= 0)
		{
			go->Destroy();
			m_bIsDead = true;
		}
	}
}

void CEnemy::Move(Vector3 _vDirection, float _MoveSpeed)
{
	tf->m_vPos += _vDirection * _MoveSpeed;
}

void CEnemy::OnDead()
{
}

