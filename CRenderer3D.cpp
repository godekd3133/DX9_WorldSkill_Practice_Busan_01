#include "DXUT.h"
#include "CRenderer3D.h"


CRenderer3D::CRenderer3D()
{
	OBJ.m_listRenderer3D.push_back(this);
}


CRenderer3D::~CRenderer3D()
{
	OBJ.m_listRenderer3D.remove(this);
}
