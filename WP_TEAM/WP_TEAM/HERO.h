#pragma once
#include "stdafx.h"

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
	int ani_frame;
	float speed;
public:
	HERO(HINSTANCE, HWND);
	~HERO();

	void update(HWND);
	MY_PFLOAT getpos() const;

	void update_hitbox();
	void draw(HDC,HWND);
	void move();
};