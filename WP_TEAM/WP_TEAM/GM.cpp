#pragma once
#include "stdafx.h"

GameManager::GameManager(){}
GameManager::~GameManager(){
	delete knight;
}

void GameManager::Game_init(HINSTANCE hInst, HWND hWnd)
{
	hwnd = hWnd;
	knight = new HERO(hInst, hwnd);
}

void GameManager::GameUpdate(HWND hWnd,float dt)
{ 
	knight->update(hwnd);
}

void GameManager::GameDraw(HDC hdc, HWND hWnd)
{
	knight->draw(hdc, hwnd);
}