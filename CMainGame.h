#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void OnLostDevice();
	void OnResetDevice();

	void AddSprite(string _Key, string _Path, int _Count = 0 );
	void AddMesh(string _Key, string _Path, string _MapPath, int _Count = 0);

	bool Success[4];
};

