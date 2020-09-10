#pragma once
#include "CRenderer3D.h"
class CMeshRenderer :
	public CRenderer3D
{
public:
	CMeshRenderer();
	~CMeshRenderer();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnRender() override;
	virtual void OnDestroy() override;
	virtual void OnCollision() override;
	
public:
	CMesh * m_pMesh;

public:
	void Init(CMesh * _pMesh, Color _Color = Color(1,1,1,1));
};

