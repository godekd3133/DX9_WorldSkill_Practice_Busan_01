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
						m_pEnemy->m_fMoveSpeed );
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
	ac<CEnemy>()->Init(MESH("ENEMY_01_IDLE (1)"), 500, 0.8f, 15, 2, 5,1.5);
	m_pEnemy = gc<CEnemy>();
	m_pEnemy->OnDead = [=]() {OnDead(); };


	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("IDLE", "ENEMY_01_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("WALK", "ENEMY_01_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK", "ENEMY_01_ATTACK", 30.f / 1000.f);

	gc<CAnimator3D>()->SetCurrentState("IDLE");

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.015, 0.015, 0.015);
}

void CEnemy01::OnAttack()
{
	tf->sa->Add(
		[=]()->bool {

		return tf->LerpScale(Vector3(0.02, 0.02, 0.02), dt * 2);

	}
	);
	gc<CMeshRenderer>()->sa->Add(
		[=]()->bool {

		return gc<CMeshRenderer>()->LerpColor(Color(1, 0, 0, 1), dt * 2);

	}
	);
	tf->sa->Add(
		[=]()->bool {
		EFFECT(tf->m_vPos, Vector3(0.01, 0.01, 0.002), "EFFECT_EXPLOSION");
		go->Destroy();
		return false;
	}
	);
}
void CEnemy01::OnDead()
{
	EFFECT(tf->m_vPos, Vector3(0.01, 0.01, 0.01), "EFFECT_ENEMY_DEAD");
	gc<CMeshRenderer>()->sa->Clear();
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