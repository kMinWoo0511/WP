#pragma once
#include "stdafx.h"

GameManager::GameManager(){}
GameManager::~GameManager(){
	delete knight;
	delete boss1;
	delete boss2;
}

void GameManager::Game_init(HINSTANCE hInst, HWND hWnd)
{
	hwnd = hWnd;
	knight = new HERO(hInst, hwnd);
	boss1 = new BOSS(hInst, hwnd);
	boss2 = new SBOSS(hInst, hwnd);
	map1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	map2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	map3 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	LOGO = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
	potal = { 1100, 685 };
	showMap = map3, SetMap = map1;
	bosstype = 2;
	logox = 200;
	logoy = 50;
	angle = 0;
}

void GameManager::GameUpdate(float dt)
{ 
	movinglogo(dt);
	//boss2->update(dt);
	//boss1->update(dt);
	knight->update(dt);
}

void GameManager::GameDraw(HDC hdc, HWND hWnd)
{
	MapDraw(hdc);
	//boss2->draw(hdc,hwnd);
	//boss1->draw(hdc, hwnd);
	knight->draw(hdc, hwnd);
}

HERO* GameManager::KnightInf()
{
	return knight;
}

BOSS* GameManager::BossInf()
{
	return boss1;
}

SBOSS *GameManager::Boss2inf()
{
	return boss2;
}

void GameManager::MapDraw(HDC memdc)
{
	HDC imagedc = CreateCompatibleDC(memdc);
	HBITMAP oldbit = (HBITMAP)SelectObject(imagedc, showMap);
	HDC logodc = CreateCompatibleDC(memdc);
	HBITMAP oldlogo = (HBITMAP)SelectObject(logodc, LOGO);

	StretchBlt(memdc, 0, 0, 1500, 900, imagedc, 0, 0, 1440, 810, SRCCOPY);
	//StretchBlt(memdc, logox, logoy, 750, 275, logodc, 0, 0, 750, 275, SRCCOPY);
	TransparentBlt(memdc, logox, logoy, 750, 275, logodc, 0, 0, 750, 275, RGB(255, 255, 255));

	SelectObject(logodc, oldlogo);
	DeleteObject(logodc);
	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void GameManager::MapSet()
{
	SetMap = map1;
}

BOOL GameManager::MapChange(float x, float y)
{
	if (potal.x - 50 <= x && x <= potal.x && potal.y + 30 >= y
		&& showMap == map3) {
		showMap = SetMap;
		return TRUE;
	}
	return FALSE;
}

int GameManager::getbosstype() const
{
	return bosstype;
}

HWND GameManager::gethWnd() const
{
	return hwnd;
}

void GameManager::movinglogo(float dt)
{
	float speed = 5 * dt;
	angle += speed;
	if (angle >= 360) angle = 0;
	logox += sin(angle) * -1;
}