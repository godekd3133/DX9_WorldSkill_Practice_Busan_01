#include "DXUT.h"
#include "CRenderer2D.h"


CRenderer2D::CRenderer2D()
{
	OBJ.m_listRenderer2D.push_back(this);
}


CRenderer2D::~CRenderer2D()
{
	OBJ.m_listRenderer2D.remove(this);
}
