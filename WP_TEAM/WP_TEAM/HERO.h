#pragma once
#include "stdafx.h"
#define KEY_DOWN(code) ((GetAsyncKeyState(code) & 0x8000 ? true : false))
#define KEY_UP(code) ((GetAsyncKeyState(code) & 0x8000 ? false : true))

enum {
	IDLE,
	RIGHT = 0,
	LEFT,
	UP,
	DOWN,
	ATTACK,
	WALK,
	JUMP,
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
	HBITMAP hero_bit;
	int ani_frame,direction,state,imgW,imgH,ani_state;
	float framedeleay,speed;

public:
	HERO(HINSTANCE, HWND);
	~HERO();

	void update(float);
	MY_PFLOAT getpos() const;
	void update_hitbox();
	void draw(HDC,HWND);
	void move(float);
	void animation(float);
};