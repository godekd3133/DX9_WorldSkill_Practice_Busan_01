#include "DXUT.h"
#include "CGameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
	for (auto iter : m_listComponent)
	{
		SAFE_DELETE(iter);
	}
	m_listComponent.clear();


}

void CGameObject::Destroy()
{
	for (auto comp : m_listComponent)
	{
		comp->sa->Clear();
		comp->OnDestroy();

	}
	for (auto iter : m_listChild)
	{
		iter->Destroy();
		iter->m_pParent = nullptr;
	}
	m_listChild.clear();
	if (m_pParent)
		m_pParent->m_listChild.remove(this);
	m_bDestroy = true;
}
