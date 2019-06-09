#pragma once
#include "stdafx.h"

BOSS::BOSS(HINSTANCE hInst, HWND hWnd)
{
	boss_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	sizeX = 60, sizeY = 60;
	pos.x = 500, pos.y = 100;
	speed = 1;
	srcpos.x = srcpos.y = 0;
	imgW = 150, imgH = 125;
	state = WALK;
	direction = LEFT;	
	pattern_state = false;
	pattern_N = 1;
}

BOSS::~BOSS()
{

}

void Matrix(MY_PFLOAT TargetPos, MY_PFLOAT OriginPos, float &x, float &y, float theta)
{
	float px = x, py = y;
	px = x * cos(theta) - y * sin(theta);
	py = x * sin(theta) + y * cos(theta);
	if (TargetPos.y < OriginPos.y) py *= -1;
	x = OriginPos.x + px, y = OriginPos.y + py;
}

MY_PFLOAT BOSS::getpos() const
{
	return pos;
}

void BOSS::update(float dt)
{
	move(dt);
	animation(dt);
	if (!pattern_state) pattern();
}

void BOSS::update_hitbox()
{
	hitbox.left = pos.x - sizeX;
	hitbox.top = pos.y - sizeY;
	hitbox.right = pos.x + sizeX;
	hitbox.bottom = pos.y + sizeY;
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
	MoveToEx(memdc, 0, UnderPos, NULL);
	LineTo(memdc, 1200, UnderPos);
}

BOOL BOSS::IsPointIncircle(float x, float y, float cx, float cy)
{
	float dx = cx - x, dy = cy - y;
	if (sqrt(dx * dx + dy * dy) <= sizeX)
		return TRUE;
	return FALSE;
}

void BOSS::CrashCheck(BOOL &Crash, BOOL& Arrive, MY_PFLOAT targetpos)
{
	RECT hero;
	SetRect(&hero, Game.KnightInf()->getpos().x - 30,
		Game.KnightInf()->getpos().y - 65,
		Game.KnightInf()->getpos().x + 30,
		Game.KnightInf()->getpos().y + 65);
	if (hero.left - sizeX <= pos.x && pos.x <= hero.right + sizeX
		&& hero.top - sizeY <= pos.y && pos.y <= hero.bottom + sizeY)
	{
		if (pos.x < hero.left && pos.y < hero.top
			&& IsPointIncircle(hero.left, hero.top, pos.x, pos.y));
		else if (pos.x > hero.right && pos.y < hero.top
			&& IsPointIncircle(hero.right, hero.top, pos.x, pos.y));
		else if (pos.x < hero.left && pos.y > hero.bottom
			&& IsPointIncircle(hero.left, hero.bottom, pos.x, pos.y));
		else if (pos.x > hero.right && pos.y > hero.bottom
			&& IsPointIncircle(hero.right, hero.bottom, pos.x, pos.y));
		else
		{
			//몬스터와 충돌
			if (Game.KnightInf()->gethit()) {
				Game.KnightInf()->setHP(Game.KnightInf()->getHP() - 1);
				Game.KnightInf()->sethitcheck(false);
				//printf("%d\n", Game.KnightInf()->getHP());
			}
		}
		/*	else
				printf("p: %f %f c: %f %f", Game.KnightInf()->pos.x, Game.KnightInf()->pos.y, pos.x, pos.y);*/
	}
	if (IsPointIncircle(targetpos.x, targetpos.y, pos.x, pos.y)) {
		Arrive = true;
		printf("inpointer: pos.x: %f pos.y: %f\n", pos.x, pos.y);
	}
	//if (UnderPos < pos.y + sizeY) {
	//	printf("A%f\n", pos.y + sizeY);
	//	pos.y =500;
	//	Crash = true;
	//}
}
#define PI 3.14159265359
#define Angle(x) x * (PI / 180)
void BOSS::move(float dt)
{
	static BOOL Crash = false, Arrive = true;
	static MY_PFLOAT targetpos = Game.KnightInf()->getpos(), originpos = Game.BossInf()->getpos();
	static float thetaVal = 0;
	static float v_ = 0, theta = 0, Countdt = 0, distance = 0;
	int g_y = 200;
	CrashCheck(Crash, Arrive, targetpos);
	Countdt += 2 * dt;
	if (Crash || Arrive) {
		float nWid, nHei;
		targetpos = Game.KnightInf()->getpos();
		originpos = Game.BossInf()->getpos();
		Crash = false, Arrive = false;
		nWid = targetpos.x - originpos.x, nHei = targetpos.y - originpos.y;
		distance = sqrt(pow(nWid, 2) + pow(nHei, 2));
		thetaVal = nWid / distance;
		Countdt = 0;
		switch (pattern_N) {
		case Pattern1:
			theta = 5 * (rand() % 8);
			printf("theta: %f\n", theta);
			theta = Angle((30 + theta));
			v_ = sqrt((distance * g_y) / (2 * sin(theta) * cos(theta)));
			break;
		case Pattern2:

			break;
		case Pattern3:

			break;
		}
	}
	pos.x = v_ * cos(theta) * Countdt;
	pos.y = v_ * sin(theta) * Countdt - 0.5 * g_y * (Countdt * Countdt);
	Matrix(targetpos, originpos, pos.x, pos.y, (acos(thetaVal))); // 선형 변환!
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