#pragma once
#include "stdafx.h"

class GameManager {
private:
	HERO *knight;
	BOSS *boss1;
	HWND hwnd;
	
public:
	GameManager();
	~GameManager();

	void Game_init(HINSTANCE,HWND);
	void GameUpdate(float);
	void GameDraw(HDC, HWND);
	HERO* KnightInf();
	BOSS* BossInf();
};