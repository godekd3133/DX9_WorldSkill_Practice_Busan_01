#include "DXUT.h"
#include "CBullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Awake()
{
}

void CBullet::Start()
{
}

void CBullet::Update()
{
	tf->m_vPos += m_vDirection * m_fSpeed * dt;
}

void CBullet::LateUpdate()
{
}

void CBullet::OnDestroy()
{
}

void CBullet::OnCollision()
{
}

void CBullet::Init(Vector3 _vPos, Vector3 _vDir, float _fSpeed)
{
	ac<CMeshRenderer>()->Init(MESH("BULLET"));

	m_fSpeed = _fSpeed;
	tf->m_vPos = _vPos + Vector3(0,2,0);
	m_vDirection = _vDir;
	tf->SetRotation(Vector3(0, my::GetDirAngle(Vector2(_vDir.z, _vDir.x)), 0));
}
