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
	float FollowDistance = m_pEnemy->m_fAttackRange;

	//Ÿ���� ������ IDLE.
	if (m_pEnemy->m_pTarget == nullptr)
		Animation_SetState("IDLE");
	//Ÿ���� �ִٸ� 
	else
	{
		//�i�ư��������� �����ϴ������� Ȯ��
		if (Animation_GetCurrentStateName == "ATTACK")
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
					GetDirection(tf->m_vPos , m_pEnemy->m_pTarget->tf->m_vPos),
					m_pEnemy->m_fMoveSpeed * dt);
				Animation_SetState("WALK");
			}
			//���� ��Ÿ� �ȿ� ��� ����
			else
			{
				tf->sa->Add(
					[=]()->bool {
	
					return tf->LerpScale(Vector3(0.02, 0.02, 0.02), dt *2 );

				}
				);
				gc<CMeshRenderer>()->sa->Add(
					[=]()->bool {

					return gc<CMeshRenderer>()->LerpColor(Color(1,0,0,1), dt * 2);

				}
				);
				tf->sa->Add(
					[=]()->bool {
					EFFECT(tf->m_vPos, Vector3(0.01, 0.01, 0.002), "EFFECT_EXPLOSION");
					go->Destroy();
					return false;
				}
				);

				Animation_SetState("ATTACK");
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
	ac<CEnemy>()->Init(MESH("ENEMY_01_IDLE (1)"), 100, 1, 15, 2, 5);
	m_pEnemy = gc<CEnemy>();


	ac<CAnimator3D>();

	gc<CAnimator3D>()->AddState("IDLE", "ENEMY_01_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("WALK", "ENEMY_01_WALK", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK", "ENEMY_01_ATTACK", 30.f / 1000.f);

	gc<CAnimator3D>()->SetCurrentState("IDLE");

	tf->m_vPos = _vPos;
	tf->m_vScale = Vector3(0.01, 0.01, 0.01);
}
