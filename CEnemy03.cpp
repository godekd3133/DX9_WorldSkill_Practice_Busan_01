#include "DXUT.h"
#include "CEnemy03.h"


CEnemy03::CEnemy03()
{
}


CEnemy03::~CEnemy03()
{
}

void CEnemy03::Awake()
{
}

void CEnemy03::Start()
{
}

void CEnemy03::Update()
{
	if (m_pEnemy->m_bIsDead == false)
	{
		float FollowDistance = m_pEnemy->m_fAttackRange;

		//타겟이 없으면 IDLE.
		if (m_pEnemy->m_pTarget == nullptr)
			Animation_SetState("IDLE");
		//타겟이 있다면 
		else
		{
			//쫒아가는중인지 공격하는중인지 확인
			if (Animation_GetCurrentStateName == "ATTACK")
			{
				if (Animation_GetNormalizeTime >= 0.99f)
					Animation_SetState("IDLE");
			}
			else
			{
				//공격 사거리에 가까워질때까지 걷기
				if (GetLength(m_pEnemy->m_pTarget->tf->m_vPos, tf->m_vPos) > FollowDistance)
				{
					m_pEnemy->Move(
						GetDirection(tf->m_vPos, m_pEnemy->m_pTarget->tf->m_vPos),
						m_pEnemy->m_fMoveSpeed);
					Animation_SetState("WALK");
				}
				//공격 사거리 안에 들면 공격
				else
				{
					OnAttack();
					Animation_SetState("ATTACK");
				}
			}
		}
	}
}

void CEnemy03::LateUpdate()
{
}

void CEnemy03::OnDestroy()
{
}

void CEnemy03::OnCollision(CGameObject * _pObject)
{
}

void CEnemy03::Init(Vector3 _vPos)
{
	ac<CEnemy>()->Init(MESH("ENEMY_03_IDLE (1)"), 2000, 1.5f, 15, 6, 3, 2.6f);
	m_pEnemy = gc<CEnemy>();
	m_pEnemy->OnDead = [=]() {OnDead(); };


	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("IDLE", "ENEMY_03_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("WALK", "ENEMY_03_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK", "ENEMY_03_ATTACK", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("DEAD", "ENEMY_03_DEAD", 30.f / 1000.f, false);

	gc<CAnimator3D>()->SetCurrentState("IDLE");

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.015, 0.015, 0.015);
}

void CEnemy03::OnAttack()
{

}
void CEnemy03::OnDead()
{
	gc<CMeshRenderer>()->sa->Clear();
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {
		gc<CAnimator3D>()->SetCurrentState("DEAD");
		if (Animation_GetNormalizeTime > 0.99f)
		{
			EFFECT(tf->m_vPos, Vector3(0.01, 0.01, 0.01), "EFFECT_ENEMY_DEAD");
			return false;
		}
		return true;
	});
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {
		return gc<CMeshRenderer>()->LerpColor(Color(1, 1, 1, 0), 4 * dt);
	});
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {
		go->Destroy();
		return false;
	});
}