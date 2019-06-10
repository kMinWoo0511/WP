#include "stdafx.h"

SBOSS::SBOSS(HINSTANCE hInst, HWND hWnd)
{
	bossbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	pos.x = 1000;
	pos.y = 685;
	state = prev_state = BWARP;
	ani_frame = framedeleay = Pattern = Patterndeleay = 0;
	direction = BLEFT;
	HP = 30;
	randomPatternTime = rand() % 7;
	attackspeed = ATTACKSPEED;
	speed = BOSSSPEED;
	ani_frame = framedeleay = warpdeleay = 0;
	warp = false;
	update_hitbox();
}

SBOSS::~SBOSS()
{

}

void SBOSS::update(float dt)
{
	update_state(dt);
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

	FillRect(memdc, &hitbox, (HBRUSH)GetStockObject(GRAY_BRUSH));

	TransparentBlt(memdc, boss_pos.x, boss_pos.y, 250, 250, imagedc, srcpos.x + 300 * ani_frame, srcpos.y, 300, 300, RGB(255, 255, 255));

	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void SBOSS::move(float dt)
{
	float dt_speed = 0;
	switch (state)
	{
	case BIDLE:
		break;
	case BWALK:
		dt_speed = speed * dt;
		if (direction == BLEFT) {
			pos.x -= dt_speed;
			if (hitbox.left <= 0) direction = BRIGHT;
		}		
		if (direction == BRIGHT) {
			pos.x += dt_speed;
			if (hitbox.right >= 1500) direction = BLEFT;
		}
		break;
	case BATTACK:
		dt_speed = attackspeed * dt;
		if (direction == BLEFT)		 pos.x	-= dt_speed;
		if (direction == BRIGHT)	 pos.x	+= dt_speed;
		break;
	case BWARP:
		if (warp)
		{
			warpdeleay += dt;
			pos.x = pos.y = 3000;
			if (warpdeleay >= WARPTIME)
			{
				warpdeleay = 0;
				warp = false;
				pos.x = Game.KnightInf()->getHeropos().x + 100;
				pos.y = Game.KnightInf()->getHeropos().y - 300;
				state = BDROPATTACK;
			}
		}
		break;
	case BDROPATTACK:
		pos.y += speed * dt;
		if (pos.y <= 635)
		{
			pos.y = 635;
			direction = rand() % 1 ? BLEFT : BRIGHT;
			state = rand() % 1;
		}
		break;
	case BDIE:
		break;
	}
}

void SBOSS::animation(float dt)
{
	switch (state)
	{
	case BIDLE:
		srcpos = makepos(direction == BLEFT ? 0 : 2100, 0);
		framedeleay += dt;
		if (framedeleay >= 0.9f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 3) ani_frame = 0;
		}
		break;
	case BWALK:
		srcpos = makepos(direction == BLEFT ? 0 : 1800, 300);
		framedeleay += dt;
		if (framedeleay >= 0.11f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) ani_frame = 0;
		}
		break;
	case BATTACK:
		srcpos = makepos(0, direction == BLEFT ? 600 : 900);
		framedeleay += dt;
		if (framedeleay >= 0.15f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 6) {
				ani_frame = 0;
				state = BIDLE;
			}
		}
		break;
	case BWARP:
		srcpos = makepos(0, direction == BLEFT ? 1200 : 1500);
		framedeleay += dt;
		if (framedeleay >= 0.2f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) {
				ani_frame = 0;
				warp = true;
			}
		}
		break;
	case BDROPATTACK:
		srcpos = makepos(0, direction == BLEFT ? 2100 : 1800);
		framedeleay += dt;
		if (framedeleay >= 0.15f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 3) ani_frame = 0;
		}
		break;
	case BDIE:
		srcpos = makepos(direction == BLEFT ? 0 : 1800, 2400);
		framedeleay += dt;
		if (framedeleay >= 0.3f) {
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 4) ani_frame = 0;
		}
		break;
	}
}

void SBOSS::update_state(float dt)
{
	Patterndeleay += dt;

	if (Patterndeleay >= 1)
	{
		randomPatternTime = rand() % 10;
		Patterndeleay = 0;
		ani_frame = 0;
		framedeleay = 0;
		int temp = rand() % 5;
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
	hitbox.right = pos.x + 60;
	hitbox.bottom = pos.y + 100;
}

int SBOSS::getaniframe() const
{
	return ani_frame;
}

int SBOSS::getstate() const
{
	return state;
}

int SBOSS::gethp() const
{
	return HP;
}

void SBOSS::sethp(int hp)
{
	HP = hp;
}

void SBOSS::hitdamgetohp(int damage)
{
	HP -= damage;
}

RECT SBOSS::gethitbox() const
{
	return hitbox;
}