#include "stdafx.h"

SBOSS::SBOSS(HINSTANCE hInst, HWND hWnd)
{
	bossbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	pos.x = 600;
	pos.y = 600;
	state = prev_state = BIDLE;
	ani_frame = framedeleay = Pattern = Patterndeleay = 0;
	direction = BLEFT;
	update_hitbox();
}

SBOSS::~SBOSS()
{

}

void SBOSS::update(float dt)
{
	move(dt);
	animation(dt);
}

void SBOSS::draw(HDC memdc, HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, bossbitmap);
	RECT temp;
	GetClientRect(hWnd, &temp);
	
	MY_PFLOAT boss_pos;
	boss_pos.x = pos.x - 150;
	boss_pos.y = pos.y - 150;
	update_hitbox();

	FillRect(memdc, &hitbox, (HBRUSH)GetStockObject(WHITE_BRUSH));

	TransparentBlt(memdc, boss_pos.x, boss_pos.y, 250, 250, imagedc, srcpos.x + 300 * ani_frame, srcpos.y, 300, 300, RGB(255, 255, 255));

	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void SBOSS::move(float dt)
{

}

void SBOSS::animation(float dt)
{
	switch (state)
	{
	case BIDLE:
		srcpos = makepos(direction == LEFT ? 2100 : 0, 0);
		framedeleay += dt;
		if (framedeleay >= 0.3f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 2) ani_frame = 0;
		}
		break;
	case BWALK:
		srcpos = makepos(direction == LEFT ? 0 : 1800, 300);
		framedeleay += dt;
		if (framedeleay >= 0.11f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) ani_frame = 0;
		}
		break;
	case BATTACK:
		srcpos = makepos(0, direction == LEFT ? 600 : 900);
		framedeleay += dt;
		if (framedeleay >= 0.15f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 6) ani_frame = 0;
		}
		break;
	case BWARP:
		srcpos = makepos(0, direction == LEFT ? 1200 : 1500);
		framedeleay += dt;
		if (framedeleay >= 0.15f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) ani_frame = 0;
		}
		break;
	case BDROPATTACK:
		srcpos = makepos(0, direction == LEFT ? 2100 : 1800);
		framedeleay += dt;
		if (framedeleay >= 0.15f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 3) ani_frame = 0;
		}
		break;
	case BDIE:
		srcpos = makepos(direction == LEFT ? 0 : 1800, 2400);
		framedeleay += dt;
		if (framedeleay >= 0.3f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) ani_frame = 0;
		}
		break;
	}
}

MY_PFLOAT SBOSS::getpos() const
{
	return pos;
}

POINT SBOSS::makepos(int x, int y)
{
	POINT point;
	point.x = x, point.y = y;
	return point;
}

void SBOSS::update_hitbox()
{
	hitbox.left = pos.x - 125;
	hitbox.top = pos.y - 125;
	hitbox.right = pos.x + 100;
	hitbox.bottom = pos.y + 100;
}