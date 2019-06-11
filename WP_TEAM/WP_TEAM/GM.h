#pragma once
#include "stdafx.h"

class GameManager {
private:
	HERO *knight;
	BOSS *boss1;
	SBOSS *boss2;
	HWND hwnd;
	HBITMAP map1, map2, map3, showMap, SetMap, LOGO;
	POINT potal;
	int bosstype;
	float logox, logoy;
	float angle;
public:
	GameManager();
	~GameManager();

	void Game_init(HINSTANCE,HWND);
	void GameUpdate(float);
	void GameDraw(HDC, HWND);
	void MapDraw(HDC);
	void MapSet();
	BOOL MapChange(float, float);
	HERO* KnightInf();
	BOSS* BossInf();
	SBOSS* Boss2inf();
	int getbosstype() const;
	HWND gethWnd() const;
	void movinglogo(float);
};