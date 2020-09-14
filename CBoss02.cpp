#include "DXUT.h"
#include "CBoss02.h"


CBoss02::CBoss02()
{
}


CBoss02::~CBoss02()
{
}

void CBoss02::Awake()
{
}

void CBoss02::Start()
{
}

void CBoss02::Update()
{
	if (m_pEnemy->m_bIsDead == false)
	{
		float FollowDistance = m_pEnemy->m_fAttackRange;

		//Ÿ���� ������ IDLE.
		if (m_pEnemy->m_pTarget == nullptr)
			Animation_SetState("IDLE");
		//Ÿ���� �ִٸ� 
		else
		{
			//�i�ư��������� �����ϴ������� Ȯ��
			if (Animation_GetCurrentStateName == "ATTACK_01" ||
				Animation_GetCurrentStateName == "ATTACK_02")
			{
				if (Animation_GetNormalizeTime >= 0.99f)
					Animation_SetState("IDLE");
			}
			else
			{
				//���� ��Ÿ��� ������������� �ȱ�
				if (GetLength(m_pEnemy->m_pTarget->tf->m_vPos, tf->m_vPos) > FollowDistance)
				{
					m_pEnemy->Move(
						GetDirection(tf->m_vPos, m_pEnemy->m_pTarget->tf->m_vPos),
						m_pEnemy->m_fMoveSpeed);
					Animation_SetState("WALK");
				}
				//���� ��Ÿ� �ȿ� ��� ����
				else
				{
					OnAttack();
					Animation_SetState("ATTACK_0" + to_string(RandRange(1, 3)));
				}
			}
		}
	}
}

void CBoss02::LateUpdate()
{
}

void CBoss02::OnDestroy()
{
}

void CBoss02::OnCollision(CGameObject * _pObject)
{
}

void CBoss02::Init(Vector3 _vPos)
{
	ac<CEnemy>()->Init(MESH("BOSS_01_IDLE (1)"), 2000, 1.5f, 15, 6, 3, 4.f);
	m_pEnemy = gc<CEnemy>();
	m_pEnemy->OnDead = [=]() {OnDead(); };

	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("IDLE", "BOSS_02_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("WALK", "BOSS_02_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK_01", "BOSS_02_ATTACK_01", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("ATTACK_02", "BOSS_02_ATTACK_02", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("SKILL", "BOSS_02_SKILL", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("DEAD", "BOSS_02_DEAD", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("BORN", "BOSS_02_BORN", 30.f / 1000.f, false);

	gc<CAnimator3D>()->SetCurrentState("IDLE");

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.02, 0.02, 0.02);
}

void CBoss02::OnAttack()
{
}

void CBoss02::OnDead()
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
