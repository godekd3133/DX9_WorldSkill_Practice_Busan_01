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
