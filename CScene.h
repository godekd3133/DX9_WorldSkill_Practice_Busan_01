#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

