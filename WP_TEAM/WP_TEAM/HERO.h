#pragma once
#include "stdafx.h"
#define KEY_DOWN(code) ((GetAsyncKeyState(code) & 0x8000 ? true : false))
#define KEY_DOWN_1(code) ((GetAsyncKeyState(code) & 0x0001 ? true : false))
#define KEY_UP(code) ((GetAsyncKeyState(code) & 0x8000 ? false : true))
#define KEY_UP_1(code) ((GetAsyncKeyState(code) & 0x0001 ? false : true))
#define JUMPPOWER 800
#define GRAVITY 1500
#define ATTACK_COOLTIME 0.5
#define SPEED 300
#define DASHSPEED 800
#define DASH_COOLTIME 1.6
#define HIT_COOLTIME 1.5
#define DAMAGE 1
#define SHOWEFFECTTIME 1
// 히어로 정보
// 공격쿨타임 0.8초
// 대쉬스킬 쿨타임 3초
// 2단점프 가능
// 공격맞은후 무적타임 1.5
enum {
	IDLE,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	JUMP,
	DOUBLEJUMP,
	DROP,
	ATTACK,
	WALK,
	DASH,
	DIE,
	RESURRECTION,
};

typedef struct {
	float x, y;
}MY_PFLOAT;

class HERO
{
private:
	HDC memdc,imagedc;
	MY_PFLOAT pos,Heropos;
	RECT hitbox,attackhitbox;
	HBITMAP hero_bit,show_bit,attack_bit,motion_bit,effect_bit;
	POINT srcpos,effectpos,srceffect;
	int ani_frame,direction,state,imgW,imgH;
	int prev_state;
	int effect_frame;
	int attack_direction;
	int doublejumpcount;
	int srcw,srch;
	int HP,damage;
	bool attack, dash;
	bool hit_check;
	bool attack_hit_check;
	float hit_cooltime;
	float framedeleay, jumpkeydeleay, prev_deleay;
	float speed, dashspeed;
	float jump_z;
	float jump_power;
	float attackdeleay,dash_cooltime;
<<<<<<< HEAD
=======
	float prev_deleay;
	std::list<EFFECT*> effectmanager;

>>>>>>> 357b60503cfb503dd81acd0a2897bd4b8cafbf5d
public:
	HERO(HINSTANCE, HWND);
	~HERO();

	void update(float);
	MY_PFLOAT getpos() const;
	void update_hitbox();
	void draw(HDC,HWND);
	void move(float);
	void animation(float);
	POINT makepos(int, int);
	int getHP() const;
	void setHP(int);
	bool gethit() const;
	void sethitcheck(bool);
	int getstate() const;
	MY_PFLOAT getHeropos() const;
	void setHeropos(float,float);
	RECT gethitbox() const;
	RECT getattackhitbox() const;
	void collision();
	void effectupdate(float);
	void effectdraw(HDC);
	void makeeffect(float, float);
};