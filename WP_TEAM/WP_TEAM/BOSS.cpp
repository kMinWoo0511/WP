#pragma once
#include "stdafx.h"
#include <time.h>

BOSS::BOSS(HINSTANCE hInst, HWND hWnd)
{
	boss_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	pos.x = 600, pos.y = 100;
	speed = 1;
	srcpos.x = srcpos.y = 0;
	imgW = 150, imgH = 125;
	state = WALK;
	direction = LEFT;
	pattern_state = false;
}

BOSS::~BOSS()
{

}

MY_PFLOAT BOSS::getpos() const
{
	return pos;
}

void BOSS::update(float dt)
{
	CrashCheck();
	move(dt);
	animation(dt);
	if (!pattern_state) pattern();
}

void BOSS::update_hitbox()
{
	hitbox.left = pos.x - 60;
	hitbox.top = pos.y - 60;
	hitbox.right = pos.x + 60;
	hitbox.bottom = pos.y + 60;
}

void BOSS::draw(HDC memdc, HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, boss_bit);
	RECT temp;
	GetClientRect(hWnd, &temp);
	//FillRect(memdc, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));

	MY_PFLOAT boss_pos;
	boss_pos.x = pos.x - 75;
	boss_pos.y = pos.y - 62.5;

	TransparentBlt(memdc, boss_pos.x, boss_pos.y, imgW, imgH, imagedc, srcpos.x + 150 * ani_frame, srcpos.y, 150, 125, RGB(55,81,59));

	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
	MoveToEx(memdc, 0, 700, NULL);
	LineTo(memdc, 1200, 700);
}

BOOL IsPointIncircle(float x, float y, float cx, float cy)
{
	float dx = cx - x, dy = cy - y;
	if (60 <= sqrt(dx * dx + dy * dy))
		return FALSE;
	return TRUE;
}

void BOSS::CrashCheck()
{
	RECT hero;
	SetRect(&hero, Game.KnightInf()->getpos().x - 30,
		Game.KnightInf()->getpos().y - 65,
		Game.KnightInf()->getpos().x + 30,
		Game.KnightInf()->getpos().y + 65);
	if (hero.left - 60 <= getpos().x && getpos().x <= hero.right + 60
		&& hero.top - 60 <= getpos().y && getpos().y <= hero.bottom + 60)
	{
		if (getpos().x < hero.left && getpos().y < hero.top
			&& !IsPointIncircle(hero.left, hero.top, getpos().x, getpos().y));
		else if (getpos().x > hero.right && getpos().y < hero.top
			&& !IsPointIncircle(hero.right, hero.top, getpos().x, getpos().y));
		else if (getpos().x < hero.left && getpos().y > hero.bottom
			&& !IsPointIncircle(hero.left, hero.bottom, getpos().x, getpos().y));
		else if (getpos().x > hero.right && getpos().y > hero.bottom
			&& !IsPointIncircle(hero.right, hero.bottom, getpos().x, getpos().y));
		else
			printf("p: %f %f c: %f %f", Game.KnightInf()->getpos().x, Game.KnightInf()->getpos().y, pos.x, pos.y);
	}
}

void BOSS::move(float dt)
{
	switch (pattern_N)
	{
	case Pattern1:
	{
		float dt_speed = (speed * 100) * dt;
		static float v1 = 0, v0 = 0, a = 3;
		float dx, dy, abs;
		MY_PFLOAT p1, p2;
		p1 = Game.KnightInf()->getpos();
		p2 = pos;
		dx = p1.x - p2.x, dy = 700 - p2.y;
		if (dx > 0) dx *= 2;
		if (dx < 0) dx *= 2;
		abs = sqrt(dx * dx + dy * dy);
		dx /= abs, dy /= abs;
		dx *= fabs(v1);
		v0 = v1;
		if (p2.y >= 700 - 60) {
			v1 *= -1;
			v0 = v1;
		}
		v1 = v0 + a * dt;
		/*switch (knight->getDir()) {
		case LEFT:
			if (dx > 0)
				dx += 1;
			break;
		case RIGHT:
			if (dx < 0)
				dx -= 1;
			break;
		case UP:
			dy += 0.5;
			break;
		case DOWN:
			dy -= 0.5;
			break;
		}*/
		pos.x += dx, pos.y += v1;
	}
		break;
	case Pattern2:

		break;
	case Pattern3:

		break;
	}
}

void BOSS::animation(float dt)
{
	switch (state)
	{
	case IDLE: // 멈춰있는 상태 - 애니메이션 만들어야함
		srcpos = makepos(0, direction == RIGHT ? 0 : 125);
		ani_frame = 0;
		break;
	case WALK:
		srcpos = makepos(0, direction == RIGHT ? 0 : 125);
		framedeleay += dt;
		if (framedeleay >= 0.05f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 12) ani_frame = 0;
		}
		break;
	}
}

void BOSS::pattern()
{
	srand((unsigned)time(NULL));
	pattern_N = 1;//rand() % 3 + 1;
}

int BOSS::getSpeed() const
{
	return speed;
}

POINT BOSS::makepos(int x, int y)
{
	POINT point;
	point.x = x, point.y = y;
	return point;
}