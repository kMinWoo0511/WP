#include "stdafx.h"

HERO::HERO(HINSTANCE hInst,HWND hWnd)
{
	//hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	attack_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	motion_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	show_bit = hero_bit;
	pos.x = 500;
	pos.y = 500;
	srcpos.x = srcpos.y = 0;
	srceffect = effectpos = srcpos;
	speed = SPEED;
	effect_frame = 0;
	dashspeed = DASHSPEED;
	imgW = 100;
	imgH = 150;
	srcw = srch =0;
	state = IDLE;
	HP = 5;
	//MoveStop = false;
	attack = false;
	jumpattack_check = false;
	attack_direction = 0;
	direction = RIGHT;
	prev_state = NULL;
	jump_z = 0;
	dash = false;
	hit_check = true;
	hit_cooltime = 0;
	jumpkeydeleay = 0;
	doublejumpcount = 0;
	attackdeleay = dash_cooltime = 5;
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
	animation(dt);
	move(dt);
}

void HERO::update_hitbox()
{
	hitbox.left = pos.x - 25;
	hitbox.top = pos.y - 45;
	hitbox.right = pos.x + 25;
	hitbox.bottom = pos.y + 45;
}

void HERO::draw(HDC memdc,HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, show_bit);
	RECT temp;
	GetClientRect(hWnd, &temp);
	FillRect(memdc, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));


	MY_PFLOAT hero_pos = this->getpos();
	hero_pos.x -= (imgW+srcw) / 2 + 0;
	hero_pos.y -= jump_z + (imgH+srch) / 2;
	TransparentBlt(memdc, hero_pos.x, hero_pos.y, (imgW+srcw), (imgH+srch), imagedc, srcpos.x + (imgW+srcw) * ani_frame, srcpos.y, (imgW+srcw), (imgH+srch), RGB(250, 247, 247));

	if (attack)
	{
		TransparentBlt(memdc, hero_pos.x + effectpos.x, hero_pos.y + effectpos.y, 150, 190, imagedc, srceffect.x + 205 * effect_frame, srceffect.y, 200, 190, RGB(255, 255, 255));
	}

	
	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void HERO::move(float dt)
{
	float dt_speed = speed * dt;
	
	if (state != JUMP && state != DROP && state != ATTACK && state != DASH) prev_state = state = IDLE;

	if (KEY_DOWN(VK_UP))
	{
		if(state != ATTACK)
		attack_direction = TOP;
	}
	if (KEY_DOWN(VK_LEFT))
	{
		if (state != ATTACK && state != DASH)
		{
			pos.x -= dt_speed;
			attack_direction = LEFT;
		}
		if (state != JUMP && state != DROP && state != ATTACK && state != DASH)
		{
			state = WALK;
			attack_direction = direction = LEFT;
		}
		if(state != DASH) direction = LEFT;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		if (state != ATTACK)
		attack_direction = BOTTOM;
		
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		if (state != ATTACK && state != DASH)
		{
			pos.x += dt_speed;
			attack_direction = RIGHT;
		}

		if (state != JUMP && state != DROP && state != ATTACK && state != DASH) {
			
			state = WALK;
			attack_direction = direction = RIGHT;
		}
		if (state != DASH) direction = RIGHT;
		
	}
	if (KEY_DOWN('Z')) {
		
		if(doublejumpcount == 0) jumpkeydeleay += dt;
		if (doublejumpcount < 2 && state != ATTACK && prev_state != ATTACK && state != DASH && prev_state != DASH) state = JUMP;
	}

	if (KEY_DOWN('X'))
	{	
		if (!attack && attackdeleay >= ATTACK_COOLTIME && state != DASH)
		{
			attackdeleay = 0;
			ani_frame = 0;
			prev_state = state;
			state = ATTACK;
			attack = true;
		}
	}
	if (attackdeleay <= ATTACK_COOLTIME) {
		attackdeleay += dt;
	}

	if (KEY_DOWN('C')) {
		if (!dash && dash_cooltime >= DASH_COOLTIME && state != ATTACK) {
			framedeleay = 0;
			dash_cooltime = 0;
			ani_frame = 0;
			prev_state = state;
			state = DASH;
			dash = true;
		}
	}
	if (dash_cooltime <= DASH_COOLTIME) {
		dash_cooltime += dt;
	}

	//충돌쿨타임계산
	if (state != DASH)
	{
		if (hit_check == false)
		{
			hit_cooltime += dt;
			if (hit_cooltime >= HIT_COOLTIME)
			{
				hit_cooltime = 0;
				hit_check = true;
			}
		}
	}
	
	//HP가 0일경우
	if (HP == 0)
	{
		//죽는것 구현하기
		printf("die\n");
	}
}

void HERO::animation(float dt)
{
	switch (state)
	{
	case IDLE: // 멈춰있는 상태 - 애니메이션 만들어야함
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(direction == RIGHT ? 0 : 600, 0);
		jumpattack_check = false;
		attack_direction = direction;
		framedeleay += dt;
		ani_frame = 0;
		break;
	case WALK:
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(0, direction == RIGHT ? 150 : 300);
		framedeleay += dt;
		if (framedeleay >= 0.1f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame == 9) ani_frame = 5;
		}
		break;
	case JUMP:
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(direction == RIGHT ? 0 : 600, 450);
		framedeleay += dt;
		if (framedeleay < 0.1f)
		{
			
			jump_power = JUMPPOWER;
			ani_frame = 0;
			break;
		}

		jump_z += jump_power * dt;
		jump_power -= GRAVITY * dt;
		
		if (framedeleay > 0.2f) ani_frame = 1;
		if (framedeleay > 0.4f) ani_frame = 2;
		if (framedeleay > 0.5f) ani_frame = 3;

		if (jump_power <= 0)
		{
			doublejumpcount++;
			ani_frame = 0;
			jump_power = 0;
			state = DROP;
			framedeleay = 0;
		}
		break;
	case DROP:
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(direction == RIGHT ? 0 : 600, 600);
		jump_z -= jump_power * dt;
		jump_power += GRAVITY * dt;
		framedeleay += dt;
		
		if (jump_z <= 0) //착지
		{
			prev_state = JUMP;
			jumpkeydeleay = 0;
			doublejumpcount = 0;
			ani_frame = 0;
			framedeleay = 0;
			jump_z = 0;
			doublejumpcount = 0;
			state = IDLE;
		}
		else //낙하중
		{
			if (framedeleay >= 0.05f) ani_frame = 0;
			if (framedeleay >= 0.25f) ani_frame = 1;
			if (framedeleay >= 0.35f) ani_frame = 2;
		}
		break;
	case ATTACK:
		if (attack)
		{
			if (prev_state == JUMP)
			{
				jumpattack_check = true;
				jump_z += jump_power * dt;
				jump_power -= GRAVITY * dt;
			
			}
			else if (prev_state == DROP)
			{
				jumpattack_check = true;
				jump_z -= jump_power * dt;
				jump_power += GRAVITY * dt;
			}

			show_bit = attack_bit;
			srcw = 90;
			srch = 40;
			framedeleay += dt;
			int effext_max = 4;
			switch (attack_direction)
			{
			case TOP:
				srcpos = makepos(0, 444);
				srceffect = makepos(800, 800);
				effectpos = makepos(40, -190);
				break;
			case BOTTOM:
				srcpos = makepos(0, 613);
				srceffect = makepos(1200, 800);
				effectpos = makepos(40, 110);
				break;
			case LEFT:
				srcpos = makepos(800, 0);
				srceffect = makepos(-15, 1000);
				effectpos = makepos(-110, 0);
				break;
			case RIGHT:
				srcpos = makepos(0, 0);
				srceffect = makepos(0, 808);
				effectpos = makepos(180, 0);
				break;
			}
			if (framedeleay >= 0.07f)
			{
				framedeleay = 0;
				ani_frame++;
				effect_frame++;
				if (attack_direction == TOP || attack_direction == BOTTOM)
				{
					effect_frame = 0;
				}
				if (ani_frame >= 4) {
					ani_frame = 0;
					effect_frame = 0;
					attack = false;
					if (prev_state == JUMP)
					{
						prev_state = ATTACK;
						state = DROP;
					}
					else {
						state = prev_state;
					}
				}
				
			}
		}
		break;
	case DASH:
		if (dash)
		{
			hit_check = false; //무적
			show_bit = motion_bit;
			srcw = 100;
			srch = 50;
			srcpos = makepos(direction == RIGHT ? 0 : 1600, 0);

			/*if (prev_state == JUMP)
			{
				jump_z += jump_power * dt;
				jump_power -= GRAVITY * dt;

			}*/
			/*if (prev_state == DROP)
			{
				jump_z -= jump_power * dt;
				jump_power += GRAVITY * dt;
			}
*/
			if (direction == RIGHT)
			{
				pos.x += dashspeed * dt;
			}
			if (direction == LEFT)
			{
				pos.x -= dashspeed * dt;
			}

			framedeleay += dt;
			if (framedeleay >= 0.1f)
			{
				framedeleay = 0;
				ani_frame++;
				if (ani_frame >= 4) {
					ani_frame = 0;
					effect_frame = 0;
					hit_check = true; //무적 해제
					dash = false;
					if (prev_state == JUMP)
					{
						prev_state = DASH;
						state = DROP;
					}
					else if(prev_state == DROP){
						state = prev_state;
						prev_state = DASH;
					}
					else {
						state = IDLE;
						prev_state = DASH;
					}
					
				}
			}
		}
		
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

int HERO::getHP() const
{
	return HP;
}

bool HERO::gethit() const
{
	return hit_check;
}

void HERO::setHP(int hp)
{
	HP = hp;
}

void HERO::sethitcheck(bool hitcheck)
{
	hit_check = hitcheck;
}

int HERO::getstate() const
{
	return state;
}