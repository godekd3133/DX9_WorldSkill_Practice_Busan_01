#include "DXUT.h"
#include "CComponent.h"


CComponent::CComponent()
{
	sa = new CScheduleAdmin();
}


CComponent::~CComponent()
{
	SAFE_DELETE(sa);
}
