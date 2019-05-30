#pragma once
#include "stdafx.h"

class GameManager {
private:
	HERO *knight;
	HWND hwnd;
	
public:
	GameManager();
	~GameManager();

	void Game_init(HINSTANCE,HWND);
	void GameUpdate(float);
	void GameDraw(HDC, HWND);
};