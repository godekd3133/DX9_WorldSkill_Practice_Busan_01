#pragma once
class CAnimation3D
{
	friend class CAnimator3D;
public:
	CAnimation3D();
	~CAnimation3D();

private:
	vector<CMesh *> m_vecMesh;

public:
	int m_iMaxFrame;
	int m_iCurFrame;
	string m_Name;
	bool m_bEnable;
private:	
	CMeshRenderer * MeshRenderer;

	bool m_bRepeat;
	float m_fDelay;
	float m_fTime = 0.f; 

	map<int, list<Event>> m_mapEvent;

public:
	void Update();

	void AddEvent(int _State, Event _Event);
	float GetNormalizeTime() { return (float)m_iCurFrame / (float)(m_iMaxFrame-1); }
	CMesh * GetCurrentMesh() { return m_vecMesh[m_iCurFrame]; }
};

