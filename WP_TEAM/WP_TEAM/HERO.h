#pragma once
#include "stdafx.h"
#define KEY_DOWN(code) ((GetAsyncKeyState(code) & 0x8000 ? true : false))
#define KEY_UP(code) ((GetAsyncKeyState(code) & 0x8000 ? false : true))
#define JUMPPOWER 800
#define GRAVITY 1500
#define ATTACK_COOLTIME 0.8
#define SPEED 300
#define DASHSPEED 800
#define DASH_COOLTIME 1.6
#define HIT_COOLTIME 1.5

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
	DROP,
	ATTACK,
	WALK,
	DASH,
	DIE,
};

typedef struct {
	float x, y;
}MY_PFLOAT;

class HERO
{
private:
	HDC memdc,imagedc;
	MY_PFLOAT pos;
	RECT hitbox;
	HBITMAP hero_bit,show_bit,attack_bit,motion_bit;
	POINT srcpos,effectpos,srceffect;
	int ani_frame,direction,state,imgW,imgH;
	int prev_state;
	int effect_frame;
	int attack_direction;
	int doublejumpcount;
	int srcw,srch;
	int HP;
	short MoveStop;
	bool attack,jumpattack_check,dash;
	bool hit_check;
	float hit_cooltime;
	float framedeleay,jumpkeydeleay;
	float speed, dashspeed;
	float jump_z;
	float jump_power;
	float attackdeleay,dash_cooltime;

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
};