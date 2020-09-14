#include "DXUT.h"
#include "CEnemy02.h"


CEnemy02::CEnemy02()
{
}


CEnemy02::~CEnemy02()
{
}

void CEnemy02::Awake()
{
}

void CEnemy02::Start()
{
}

void CEnemy02::Update()
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
			if (Animation_GetCurrentStateName == "ATTACK_01"||
				Animation_GetCurrentStateName == "ATTACK_02")
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
					Animation_SetState("ATTACK_0" + to_string(RandRange(1,3)));
				}
			}
		}
	}
}

void CEnemy02::LateUpdate()
{
}

void CEnemy02::OnDestroy()
{
}

void CEnemy02::OnCollision(CGameObject * _pObject)
{
}

void CEnemy02::Init(Vector3 _vPos)
{
	ac<CEnemy>()->Init(MESH("ENEMY_02_IDLE (1)"), 1500, 1.5f, 15, 8, 3,2.6f);
	m_pEnemy = gc<CEnemy>();
	m_pEnemy->OnDead = [=]() {OnDead(); };


	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("IDLE", "ENEMY_02_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("WALK", "ENEMY_02_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK_01", "ENEMY_02_ATTACK_01", 30.f / 1000.f,false);
	gc<CAnimator3D>()->AddState("ATTACK_02", "ENEMY_02_ATTACK_02", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("DEAD", "ENEMY_02_DEAD", 30.f / 1000.f, false);

	gc<CAnimator3D>()->SetCurrentState("IDLE");

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.015, 0.015, 0.015);
}

void CEnemy02::OnAttack()
{

}


void CEnemy02::OnDead()
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