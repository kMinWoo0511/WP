#include "stdafx.h"

HERO::HERO(HINSTANCE hInst,HWND hWnd)
{
	//hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hero_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	attack_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	motion_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	effect_bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
	show_bit = hero_bit;
	pos.x = 600;
	pos.y = 685;
	Heropos = {0,0};
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
	attack = attack_hit_check =false;
	attack_direction = 0;
	direction = RIGHT;
	prev_state = NULL;
	jump_z = 0;
	dash = false;
	hit_check = true;
	hit_cooltime = 0;
<<<<<<< HEAD
	jumpkeydeleay = 0, prev_deleay;
=======
	prev_deleay =0;
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
	doublejumpcount = 0;
	attackdeleay = dash_cooltime = 5;
	damage = DAMAGE;
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
	effectupdate(dt);
	collision();
	animation(dt);
	move(dt);
}

void HERO::update_hitbox()
{
	hitbox.left		= Heropos.x + 35;
	hitbox.top		= Heropos.y + 45;
	hitbox.right	= Heropos.x + imgW - 24;
	hitbox.bottom	= Heropos.y + imgH - 12;
}

void HERO::draw(HDC memdc,HWND hWnd)
{
	HBITMAP oldbit;
	imagedc = CreateCompatibleDC(memdc);
	oldbit = (HBITMAP)SelectObject(imagedc, show_bit);
	RECT temp;
	GetClientRect(hWnd, &temp);
	//FillRect(memdc, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));

	MY_PFLOAT hero_pos = this->getpos();
	hero_pos.x -= (imgW+srcw) / 2;
	hero_pos.y -= jump_z + (imgH+srch) / 2;
	setHeropos(hero_pos.x, hero_pos.y);
	update_hitbox();
	FillRect(memdc, &hitbox, (HBRUSH)GetStockObject(WHITE_BRUSH));

	TransparentBlt(memdc, hero_pos.x, hero_pos.y, (imgW+srcw), (imgH+srch), imagedc, srcpos.x + (imgW+srcw) * ani_frame, srcpos.y, (imgW+srcw), (imgH+srch), RGB(250, 247, 247));

	if (attack)
	{
		FillRect(memdc, &attackhitbox, (HBRUSH)GetStockObject(GRAY_BRUSH));

		TransparentBlt(memdc, hero_pos.x + effectpos.x, hero_pos.y + effectpos.y, 150, 190, imagedc, srceffect.x + 205 * effect_frame, srceffect.y, 200, 190, RGB(255, 255, 255));
	}

	effectdraw(memdc); //히트이펙트

	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void HERO::move(float dt)
{
	float dt_speed = speed * dt;
	
	if (hitbox.left <= 0) pos.x += dt_speed;
	if (hitbox.right >= 1500) pos.x -= dt_speed;


<<<<<<< HEAD
	if (state != JUMP && state != DROP && state != ATTACK && state != DASH) {
		prev_state = state;
		state = IDLE;
=======
	if (state != JUMP && state != DROP && state != ATTACK && state != DASH && state != DIE && state != RESURRECTION) prev_state = state = IDLE;

	if (KEY_DOWN(VK_UP))
	{
		if(state != ATTACK)
		attack_direction = TOP;
		Game.MapChange(pos.x, pos.y);
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
	}

	if (KEY_DOWN(VK_LEFT))
	{
<<<<<<< HEAD
		if (state != DASH)
=======
		if (state != ATTACK && state != DASH && state != DIE && state != RESURRECTION)
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
		{
			pos.x -= dt_speed;
		}
		if (state != JUMP && state != DROP && state != ATTACK && state != DASH && state != DIE && state != RESURRECTION)
		{
			state = WALK;
			attack_direction = direction = LEFT;
		}
		if (state != DASH && state != ATTACK) attack_direction = direction = LEFT;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
<<<<<<< HEAD
		if (state != DASH)
=======
		if (state != ATTACK && state != DASH && state != DIE && state != RESURRECTION)
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
		{
			pos.x += dt_speed;
		}

<<<<<<< HEAD
		if (state != JUMP && state != DROP && state != ATTACK && state != DASH)
		{	
=======
		if (state != JUMP && state != DROP && state != ATTACK && state != DASH && state != DIE && state != RESURRECTION) {
			
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
			state = WALK;
			attack_direction = direction = RIGHT;
		}
		if (state != DASH && state != ATTACK) attack_direction = direction = RIGHT;
		
	}
<<<<<<< HEAD
	if (KEY_DOWN(VK_UP))
	{
		if (state != ATTACK)
			attack_direction = TOP;
		Game.MapChange(pos.x, pos.y);
	}
	if (KEY_DOWN(VK_DOWN))
	{
		if (state != ATTACK)
			attack_direction = BOTTOM;
	}
	if (KEY_DOWN_1('Z')) {
		if (doublejumpcount >= 2);
		else {
			if (state == ATTACK) {
				prev_state = JUMP;
				doublejumpcount++;
			}
			if (state != DASH) {
				jump_power += (JUMPPOWER - jump_power);
				ani_frame = 0;
			}
			if (state != ATTACK && state != DASH) state = JUMP, doublejumpcount++;
		}
	}
	if (KEY_DOWN_1('X')) {
		if (!attack && attackdeleay >= ATTACK_COOLTIME && state != DASH)
=======
	if (KEY_DOWN('Z')) {
		if (doublejumpcount < 2 && state != ATTACK && prev_state != ATTACK && state != DASH && prev_state != DASH && state != DIE && state != RESURRECTION) {
			state = JUMP;
		
		}
	}

	if (KEY_DOWN('X'))
	{	
		if (!attack && attackdeleay >= ATTACK_COOLTIME && state != DASH && state != DIE && state != RESURRECTION)
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
		{
			prev_deleay = framedeleay;
			printf("Attack\n");
			attackdeleay = 0;
			ani_frame = 0;
			prev_state = state;
			state = ATTACK;
			attack = true;
		}
		printf("x-> %f\n", prev_deleay);
	}

	if (attackdeleay <= ATTACK_COOLTIME) {
		attackdeleay += dt;
	}

	if (KEY_DOWN('C')) {
		if (!dash && dash_cooltime >= DASH_COOLTIME && state != ATTACK && state != DIE && state != RESURRECTION) {
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
		state = DIE;
	}
}

void HERO::animation(float dt)
{
	switch (state)
	{
	case IDLE: // 멈춰있는 상태 - 애니메이션 만들어야함
		if (prev_state == WALK) {
			state = WALK;
			framedeleay += dt;
			if (framedeleay > 0.13f) {
				if (10 <= ani_frame) ani_frame++;
				else ani_frame = 10;
				framedeleay = 0;
			}
			if (ani_frame >= 12) state = IDLE;
		}
		else {
			show_bit = hero_bit;
			srcw = srch = 0;
			srcpos = makepos(direction == RIGHT ? 0 : 600, 0);
			attack_direction = direction;
			framedeleay += dt;
			ani_frame = 0;
		}
		break;
	case WALK:
		state = WALK;
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(0, direction == RIGHT ? 150 : 300);
		framedeleay += dt;
		if (framedeleay >= 0.1f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 9) ani_frame = 5;
		}
		break;
	case JUMP:
		show_bit = hero_bit;
		srcw = srch = 0;
		srcpos = makepos(direction == RIGHT ? 0 : 600, 450);
		framedeleay += dt;

<<<<<<< HEAD
=======
		if (framedeleay < 0.1f)
		{
			jump_power = JUMPPOWER;
			//jump_power += (JUMPPOWER - jump_power);
			ani_frame = 0;
			break;
		}

>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
		jump_z += jump_power * dt;
		jump_power -= GRAVITY * dt;
		if (framedeleay > 0.2f) ani_frame = 1;
		if (framedeleay > 0.4f) ani_frame = 2;
		if (framedeleay > 0.5f) ani_frame = 3;
		if (jump_power < 0)
		{
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
<<<<<<< HEAD
			prev_state = DROP;
			jump_power = 0;
			jumpkeydeleay = 0;
			ani_frame = 0;
			framedeleay = 0;
=======
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
			jump_z = 0;
			jump_power = 0;
			prev_state = JUMP;
			if (framedeleay >= 0.45f) ani_frame = 3;
			if (framedeleay >= 0.55f) {
				ani_frame = 4;
				jumpkeydeleay = 0;
				doublejumpcount = 0;
				//ani_frame = 0;
				framedeleay = 0;
				doublejumpcount = 0;
				state = IDLE; 
			}
			
			
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
<<<<<<< HEAD
=======
			if (prev_state == JUMP)
			{
				prev_deleay = framedeleay;
				jumpattack_check = true;
				///jump_z += jump_power * dt;
				//jump_power -= GRAVITY * dt;
			}
			else if (prev_state == DROP)
			{
				jumpattack_check = true;
				jump_z -= jump_power * dt;
				jump_power += GRAVITY * dt;
			}

>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
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
			if (prev_state == JUMP) {
				jump_z += jump_power * dt;
				jump_power -= GRAVITY * dt;
				if (jump_power < 0) {
					prev_state = DROP;
				}
			}
			if (prev_state == DROP) {
				jump_z -= jump_power * dt;
				jump_power += GRAVITY * dt;
				if (jump_z <= 0) //착지
				{
					jump_z = 0;
				}
			}
			if (framedeleay >= 0.1f)
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
<<<<<<< HEAD
					framedeleay = prev_deleay;
					state = prev_state;
					if (state == JUMP && jump_power <= 0) {
						prev_state = ATTACK, state = DROP;
						jump_power = 0;
=======
					if (prev_state == JUMP)
					{
						framedeleay = prev_deleay;
						prev_state = ATTACK;
						state = DROP;
					}
					else {
						state = prev_state;
>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
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
	case DIE:
		show_bit = motion_bit;
		srcw = 100;
		srch = 50;
		srcpos = makepos(direction == RIGHT ? 0 : 1400, 200);
		ani_frame = 0;
		break;
	case RESURRECTION:
		show_bit = motion_bit;
		srcw = 100;
		srch = 50;
		srcpos = makepos(direction == RIGHT ? 0 : 1400, 200);
		framedeleay += dt;

		if (framedeleay >= 0.4f)
		{
			framedeleay = 0;
			ani_frame++;
			if (ani_frame >= 7) {
				state = IDLE;
				framedeleay = 0;
			}
		}
		
		break;
	}
}

void HERO::collision()
{
	if (state != ATTACK && ani_frame != 2)
	{
		attackhitbox = { -30,-30,-30,-30 };
		attack_hit_check = false;
	}

	if (state == ATTACK && ani_frame == 2)
	{
		switch (attack_direction)
		{
		case TOP:
			attackhitbox.left	= Heropos.x + 70;
			attackhitbox.top	= Heropos.y - 150;
			attackhitbox.right	= Heropos.x + 160;
			attackhitbox.bottom = Heropos.y - 30;
			break;
		case BOTTOM:
			attackhitbox.left	= Heropos.x + 90;
			attackhitbox.top	= Heropos.y + 180;
			attackhitbox.right	= Heropos.x + 180;
			attackhitbox.bottom = Heropos.y + 280;
			break;
		case LEFT:
			attackhitbox.left	= Heropos.x - 100;
			attackhitbox.top	= Heropos.y + 80;
			attackhitbox.right	= Heropos.x + 10;
			attackhitbox.bottom = Heropos.y + 130;
			break;
		case RIGHT:
			attackhitbox.left	= Heropos.x + 200;
			attackhitbox.top	= Heropos.y + 70;
			attackhitbox.right	= Heropos.x + 310;
			attackhitbox.bottom = Heropos.y + 130;
			break;
		}
	}

	RECT temp;
	if (Game.getbosstype() == 2)
	{
		if (IntersectRect(&temp, &attackhitbox, &Game.Boss2inf()->gethitbox()) && !attack_hit_check)
		{
			float efx = (temp.right - temp.left) / 2;
			float efy = (temp.bottom - temp.top) / 2;
			switch (attack_direction)
			{
			case TOP:
				efx = 0;
				break;
			case BOTTOM:
				efx = 0;
				break;
			case LEFT:
				efy = 0;
				efx *= -1;
				break;
			case RIGHT:
				efy = 0;
				break;
			}

			float hitposx = (attackhitbox.right + attackhitbox.left) / 2 + efx;
			float hitposy = (attackhitbox.top + attackhitbox.bottom) / 2 + efy;
				
			makeeffect(hitposx, hitposy);

			attack_hit_check = true;
			Game.Boss2inf()->hitdamgetohp(damage);
		}
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

MY_PFLOAT HERO::getHeropos() const
{
	return Heropos;
}

void HERO::setHeropos(float x, float y)
{
	Heropos.x = x;
	Heropos.y = y;
}

RECT HERO::gethitbox() const
{
	return hitbox;
}

RECT HERO::getattackhitbox() const {
	return attackhitbox;
}

void HERO::effectupdate(float dt)
{
	std::list<EFFECT*>::iterator iter;
	for (iter = effectmanager.begin(); iter != effectmanager.end(); iter++)
	{
		EFFECT* effect = *iter;
		if (effect != NULL)
		{
			if (effect->getshow() == false)
			{
				effectmanager.erase(iter);
				delete effect;
				break;
			}

			effect->update(dt);
		}
	}
}

void HERO::effectdraw(HDC memdc)
{
	std::list<EFFECT*>::iterator iter;
	for (iter = effectmanager.begin(); iter != effectmanager.end(); iter++)
	{
		EFFECT* effect = *iter;
		if (effect != NULL)
		{
			effect->draw(memdc);
		}
	}
}

void HERO::makeeffect(float x, float y)
{
	EFFECT *effect = new EFFECT(effect_bit);
	effect->seteffectpos(x, y);
	effectmanager.push_back(effect);
}