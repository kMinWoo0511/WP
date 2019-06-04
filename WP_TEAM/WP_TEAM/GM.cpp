#pragma once
#include "stdafx.h"

GameManager::GameManager(){}
GameManager::~GameManager(){
	delete knight;
	delete boss1;
}

void GameManager::Game_init(HINSTANCE hInst, HWND hWnd)
{
	hwnd = hWnd;
	knight = new HERO(hInst, hwnd);
	boss1 = new BOSS(hInst, hwnd);
}

void GameManager::GameUpdate(float dt)
{ 
	knight->update(dt);
	boss1->update(dt);
}

void GameManager::GameDraw(HDC hdc, HWND hWnd)
{
	knight->draw(hdc, hwnd);
	boss1->draw(hdc, hwnd);
}

HERO* GameManager::KnightInf()
{
	return knight;
}