#pragma once
#include "CSingleton.h"
enum Axis
{
	Foward,
	Back,
	Right,
	Left
};
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
	Vector3 m_vFoward = Vector3(0, 0, 1);
	Vector3 m_vCharactorAxis[4];
	Matrix m_matView;
	Matrix m_matProj;

	Vector3 m_vShakePos;
	Vector2 m_vRotation = Vector2(0,0);
	Vector3 m_vOffset = Vector3(0, 0, 0);
	float m_fCameraTime;
	float m_fShakePower;
	float m_fSensitivity = 10.f;
public:
	void Update();
	void SetTransform();
	CGameObject * m_pFollowObject = nullptr;
	float m_fDistance = 0.f;
public:
	void Shake(float _fTime, float _fPower);
	void Follow(CGameObject * _Follow, float _Distance)
	{
		m_pFollowObject = _Follow;
		m_fDistance = _Distance;
	}
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
