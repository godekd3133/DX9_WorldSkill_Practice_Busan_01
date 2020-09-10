#pragma once
class CAnimation2D
{
	friend class CAnimator2D;
public:
	CAnimation2D();
	~CAnimation2D();
private:
	vector<CSprite *> m_vecSprite;

public:
	int m_iMaxFrame;
	int m_iCurFrame;

private:
	bool m_bRepeat;
	float m_fDelay;
	float m_fTime = 0.f;
	bool m_bEnable;

	map<int, list<Event>> m_mapEvent;

public:
	void Update();

	void AddEvent(int _State, Event _Event);
	float GetNormalizeTime() { return (float)m_iCurFrame / (float)(m_iMaxFrame-1); }
	CSprite * GetCurrentSprite() {
		return m_vecSprite[m_iCurFrame];
	}
};

