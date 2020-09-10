 #include "DXUT.h"
#include "CPlayerMovement.h"

CPlayerMovement::CPlayerMovement()
{
}


CPlayerMovement::~CPlayerMovement()
{
}

void CPlayerMovement::Awake()
{
	ac<CMeshRenderer>()->Init(MESH("PLAYER_RIFLE_IDLE (1)"))
		 
}

void CPlaye rMovement::Start()
{

}

void CPlayerMovement::Update()
{
	
}

void CPlayerMovement::LateUpdate()
{
}

void CPlayerMovement::OnDestroy()
{

}

void CPlayerMovement::OnCollision(CGameObject * _pObject)
{
}

