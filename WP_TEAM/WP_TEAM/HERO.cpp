#include "stdafx.h"

HERO::HERO(HINSTANCE hInst,HWND hWnd)
{
	//hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	pos.x = 600;
	pos.y = 700;
	srcpos.x = srcpos.y = 0;
	offset.x = offset.y = 0;
	speed = 3;
	imgW = 75;
	imgH = 110;
	state = IDLE;
	attack_direction = 0;
	direction = RIGHT;
	jump_z = 0;
	jumpkeydeleay = 0;
	doublejumpcount = 0;
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
	hitbox.left = pos.x - imgW;
	hitbox.top = pos.y - imgH;
	hitbox.right = pos.x + imgW;
	hitbox.bottom = pos.y + imgH;
}

void HERO::draw(HDC memdc,HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, hero_bit);
	RECT temp;
	GetClientRect(hWnd, &temp);
	FillRect(memdc, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));

	MY_PFLOAT hero_pos = this->getpos();
	hero_pos.x -= offset.x + imgW / 2;
	hero_pos.y -= imgH + jump_z;

	TransparentBlt(memdc, hero_pos.x, hero_pos.y, imgW, imgH, imagedc, srcpos.x + 90 * ani_frame, srcpos.y, 80, 110, RGB(10, 9, 8));

	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void HERO::move(float dt)
{
	float dt_speed = (speed*100) * dt;
	
	if (state != JUMP && state != DROP) state = IDLE;

	if (KEY_DOWN(VK_UP))
	{
		attack_direction = TOP;
	}
	if (KEY_DOWN(VK_LEFT))
	{
		pos.x -= dt_speed;
<<<<<<< HEAD
		if (state != JUMP && state != DROP)	state = WALK;
		direction = LEFT;
		
=======
		if (state != JUMP && state != DROP) state = WALK;
		attack_direction = direction = LEFT;
>>>>>>> a5decc261677d432113912aa7639b6238c1bb227
	}
	if (KEY_DOWN(VK_DOWN))
	{
		attack_direction = BOTTOM;
		
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		pos.x += dt_speed;
<<<<<<< HEAD
		if (state != JUMP && state != DROP)	state = WALK;
		direction = RIGHT;
=======
		if (state != JUMP && state != DROP) state = WALK;
		attack_direction = direction = RIGHT;
>>>>>>> a5decc261677d432113912aa7639b6238c1bb227
	}

	if (KEY_DOWN('Z')) {
		
		if(doublejumpcount == 0) jumpkeydeleay += dt;
		if (doublejumpcount < 2) state = JUMP;
	}

	if (KEY_DOWN('X'))
	{	
		state = ATTACK;
	}

}

void HERO::animation(float dt)
{
	switch (state)
	{
	case IDLE: // ¸ØÃçÀÖ´Â »óÅÂ - ¾Ö´Ï¸ÞÀÌ¼Ç ¸¸µé¾î¾ßÇÔ
		srcpos = makepos(direction == RIGHT ? 0 : 795, 0);
		ani_frame = 0;
		break;
	case WALK:
		srcpos = makepos(direction == RIGHT ? 0 : 795, 140);
		framedeleay += dt;
		if (framedeleay >= 0.1f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 7) ani_frame = 0;
		}
		break;
	case JUMP:
		framedeleay += dt;
		srcpos = makepos(direction == RIGHT ? 0 : 795, 292);
		if (framedeleay < 0.1f)
		{
			jump_power = JUMPPOWER;
			printf("%f\n", jump_power);
			ani_frame = 0;
			break;
		}

		jump_z += jump_power * dt;
		jump_power -= GRAVITY * dt;
		
		if (framedeleay > 0.2f) ani_frame = 1;
		if (framedeleay > 0.4f) ani_frame = 2;

		if (jump_power <= 0)
		{
			doublejumpcount++;
			ani_frame = 2;
			jump_power = 0;
			state = DROP;
			framedeleay = 0;
		}
		break;
	case DROP:
		srcpos = makepos(direction == RIGHT ? 0 : 795, 450);
		jump_z -= jump_power * dt;
		jump_power += GRAVITY * dt;
		framedeleay += dt;
		
		if (jump_z <= 0) //ÂøÁö
		{
			jumpkeydeleay = 0;
			doublejumpcount = 0;
			ani_frame = 2;
			framedeleay = 0;
			jump_z = 0;
			doublejumpcount = 0;
			state = IDLE;
		}
		else //³«ÇÏÁß
		{
			if (framedeleay >= 0.1f) ani_frame = 0;
			if (framedeleay >= 0.25f) ani_frame = 1;
		}
		break;
	case ATTACK:
		break;
	}
}

POINT HERO::makepos(int x, int y)
{
	POINT point;
	point.x = x;
	point.y = y;
	return point;
}