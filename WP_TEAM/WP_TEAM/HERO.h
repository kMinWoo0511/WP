#pragma once
#include "stdafx.h"
#define KEY_DOWN(code) ((GetAsyncKeyState(code) & 0x8000 ? true : false))
#define KEY_UP(code) ((GetAsyncKeyState(code) & 0x8000 ? false : true))
#define JUMPPOWER 800
#define GRAVITY 1500
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
};

typedef struct {
	float x, y;
}MY_PFLOAT;

class HERO
{
private:
	HDC memdc,imagedc;
	MY_PFLOAT pos;
	MY_PFLOAT offset;
	RECT hitbox;
	HBITMAP hero_bit;
	POINT srcpos;
	int ani_frame,direction,state,imgW,imgH;
	int prev_state;
	int attack_direction;
	int doublejumpcount;
	float framedeleay,speed,jumpkeydeleay;
	float jump_z;
	float jump_power;


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
};