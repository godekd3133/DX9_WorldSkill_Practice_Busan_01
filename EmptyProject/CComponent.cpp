#include "DXUT.h"
#include "CComponent.h"


CComponent::CComponent()
{
}


CComponent::~CComponent()
{
	SAFE_DELETE(sa);
}
