#include "DXUT.h"
#include "CAnimation2D.h"


CAnimation2D::CAnimation2D()
{
}


CAnimation2D::~CAnimation2D()
{
	m_mapEvent.clear();
}

void CAnimation2D::Update()
{
	if (m_bEnable)
		m_fTime += dt;

	if (m_fTime > m_fDelay)
	{
		m_fTime = 0.f;
		m_iCurFrame++;
		if (m_iCurFrame >= m_iMaxFrame)
		{
			if (m_bRepeat == false)
			{
				m_iCurFrame--;
				m_bEnable = false;
			}
			else
				m_iCurFrame = 0;


		}
		if (auto find = m_mapEvent.find(m_iCurFrame); find != m_mapEvent.end())
		{
			for (auto iter : m_mapEvent[m_iCurFrame])
			{
				iter();
			}
		}
	}
}

void CAnimation2D::AddEvent(int _State, Event _Event)
{
	m_mapEvent[_State].push_back(_Event);
}
