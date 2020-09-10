#pragma once
#include "CSingleton.h"
class CCameraManager :
	public CSingleton< CCameraManager>
{
public:
	CCameraManager();
	~CCameraManager();

public:
	CScheduleAdmin  * sa;

	Vector3 m_vPos;
	Vector3 m_vLookAt;
	Vector3 m_vUp;

	Matrix m_matView;
	Matrix m_matProj;

	Vector3 m_vShakePos;
	float m_fCameraTime;
	float m_fShakePower;

public:
	void Update();
	void SetTransform();

public:
	void Shake(float _fTime, float _fPower);

private:
	void ShakeCamera()
	{
		m_vShakePos.x += rand() % (int)m_fShakePower - m_fShakePower / 2;
		m_vShakePos.y += rand() % (int)m_fShakePower - m_fShakePower / 2;
		m_vShakePos.z += rand() % (int)m_fShakePower - m_fShakePower / 2;
	}

public:
	bool m_bScrolling = false;
	float m_fScrollSpeed;
	float m_fCurSpeed;

};

#define CAMERA (*CCameraManager::GetInstance())
