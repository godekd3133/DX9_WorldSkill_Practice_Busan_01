#pragma once

using Schedule = function<bool()>;
class CScheduleAdmin
{
public:
	CScheduleAdmin();
	~CScheduleAdmin();

private:
	queue<pair<Schedule, float>> m_Schedules;
	float m_fTime = 0.f;
	float m_fDurationTime = 0.f;
public:
	void Clear();
	bool Empty();
	void Add(Schedule _Schedule, float _fDuraction = 0.f);
	void Delay(float _fTime);
	void Update();
};

