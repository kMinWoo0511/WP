#include "stdafx.h"

HERO::HERO(HINSTANCE hInst,HWND hWnd)
{
	hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	pos.x = 300;
	pos.y = 300;
	speed = 3;
	imgW = 55;
	imgH = 110;
	state = IDLE;
	direction = RIGHT;
	ani_state = 0;
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

void HERO::update(float dt)
{
	move(dt);
	animation(dt);
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
	RECT temp;
	GetClientRect(hWnd, &temp);
	FillRect(memdc, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));
	TransparentBlt(memdc, pos.x, pos.y, imgW, imgH, imagedc, 0 + 60 * ani_frame, 0 + 130 * ani_state, 65, 130, RGB(10, 9, 8));
	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void HERO::move(float dt)
{
	float dt_speed = (speed*100) * dt;
	if (KEY_UP('W') || KEY_UP('A') || KEY_UP('S') || KEY_UP('D')) state = IDLE;

	if (KEY_DOWN('W'))
	{
		pos.y -= dt_speed;
	}
	if (KEY_DOWN('A'))
	{
		pos.x -= dt_speed;
		state = WALK;
		direction = LEFT;
	}
	if (KEY_DOWN('S'))
	{
		pos.y += dt_speed;
		
	}
	if (KEY_DOWN('D'))
	{
		pos.x += dt_speed;
		state = WALK;
		direction = RIGHT;
	}

}

void HERO::animation(float dt)
{
	switch (state)
	{
	case IDLE: // 멈춰있는 상태 - 애니메이션 만들어야함
		ani_frame = 0;
		ani_state = direction;
		break;
	case WALK:
		framedeleay += dt;
		ani_state = direction;
		if (framedeleay >= 0.1f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 2) ani_frame = 0;
		}
		break;
	case ATTACK:
		break;
	}
}