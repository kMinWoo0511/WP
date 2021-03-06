#pragma once
#include "stdafx.h"

enum {
	Pattern1 = 1,
	Pattern2,
	Pattern3
};

class BOSS
{
private:
	HDC memdc, imagedc;
	MY_PFLOAT pos;
	RECT hitbox;
	HBITMAP boss_bit;
	BOOL pattern_state;
	POINT srcpos;
	int ani_frame, direction, state, imgW, imgH, sizeX, sizeY, pattern_N;
	float framedeleay, speed;
public:
	BOSS(HINSTANCE, HWND);
	~BOSS();

	void update(float);
	void update_hitbox();
	void draw(HDC, HWND);
	void CrashCheck(BOOL&, BOOL&, MY_PFLOAT);
	void move(float);
	void animation(float);
	void pattern();
	BOOL IsPointIncircle(float, float, float, float);
	MY_PFLOAT getpos() const;
	POINT makepos(int, int);
	int getSpeed() const;
};