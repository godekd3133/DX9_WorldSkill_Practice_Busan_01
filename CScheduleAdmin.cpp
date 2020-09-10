#include "DXUT.h"
#include "CScheduleAdmin.h"

CScheduleAdmin::CScheduleAdmin()
{
}

CScheduleAdmin::~CScheduleAdmin()
{
}

void CScheduleAdmin::Clear()
{
	while (1)
	{
		if (!m_Schedules.empty())
			m_Schedules.pop();
		else break;
	}
}

bool CScheduleAdmin::Empty()
{
	return m_Schedules.empty();
}

void CScheduleAdmin::Add(Schedule _Schedule, float _fDuraction)
{
	m_Schedules.emplace(_Schedule, _fDuraction);
}


void CScheduleAdmin::Delay(float _fTime)
{
	m_Schedules.emplace(
		[this, _fTime]()->bool {
		m_fTime += dt;
		if (m_fTime > _fTime)
		{
			m_fTime = 0.f;
			return false;
		}
		return true;
	}, _fTime);
}

void CScheduleAdmin::Update()
{
	if (!m_Schedules.empty())
	{
		m_fDurationTime += dt;
		if (m_Schedules.front().first() == false ||
			(m_Schedules.front().second != 0.f &&m_fDurationTime > m_Schedules.front().second))
		{
			m_fDurationTime = 0.f;
			if (!m_Schedules.empty())
				m_Schedules.pop();
		}
	}
}
