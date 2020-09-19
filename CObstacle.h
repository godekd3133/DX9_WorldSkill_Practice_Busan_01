#pragma once
#include "CComponent.h"
enum class ObstacleType
{
	Thom,//가시
	Mine,//지뢰
	Trap //함정
};
class CObstacle :
	public CComponent
{
public:
	CObstacle();
	~CObstacle();
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

private:
	ObstacleType m_Type;
public:
	void Init(ObstacleType _Type, Vector3 _vPos);
};

