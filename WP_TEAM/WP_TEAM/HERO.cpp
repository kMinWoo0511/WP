#include "stdafx.h"

HERO::HERO(HINSTANCE hInst,HWND hWnd)
{
	hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	pos.x = 300;
	pos.y = 300;
	speed = 7;
	update_hitbox();
}

HERO::~HERO()
{
	DeleteObject(imagedc);
	DeleteObject(memdc);
}

MY_PFLOAT HERO::getpos() const
{
	return pos;
}

void HERO::update(HWND hWnd)
{
	move();
}

void HERO::update_hitbox()
{
	hitbox.left = pos.x - 30;
	hitbox.top = pos.y - 65;
	hitbox.right = pos.x + 30;
	hitbox.bottom = pos.y + 65;
}

void HERO::draw(HDC memdc,HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, hero_bit);
	TransparentBlt(memdc, pos.x, pos.y, 60, 130, imagedc, 0, 0, 60, 130, RGB(10, 9, 8));
	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void HERO::move()
{
	if (GetAsyncKeyState('W') & 0x8000)//위
	{
		pos.y -= speed;
	}

	if (GetAsyncKeyState('A') & 0x8000)//왼쪽
	{
		pos.x -= speed;
	}

	if (GetAsyncKeyState('S') & 0x8000)//아래
	{
		pos.y += speed;
	}
	if (GetAsyncKeyState('D') & 0x8000)//오른쪽
	{
		pos.x += speed;
	}
}