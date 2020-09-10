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

bool CRenderer3D::LerpColor(Color _Target, float _Speed)
{
	m_Color = Lerp(m_Color, _Target, _Speed);
	
	float a = abs((m_Color.a - _Target.a) * 255);
	float r = abs((m_Color.r - _Target.r) * 255);
	float g = abs((m_Color.g - _Target.g) * 255);
	float b = abs((m_Color.b - _Target.b) * 255);

	if (a < 3 && r < 3 && g < 3 && b < 3)
	{
		return false;
	}
	return true;



}
