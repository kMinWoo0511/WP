#pragma once
#include "stdafx.h"

enum {
	BIDLE,
	BWALK,
	BATTACK,
	BWARP,
	BDROPATTACK,
	BDIE,
	BRIGHT,
	BLEFT,
};

enum {
	PATTERN1,
	PATTERN2,
	PATTERN3,
};

class SBOSS {
private:
	HBITMAP bossbitmap;
	MY_PFLOAT pos;
	HDC imagedc;
	POINT srcpos;
	RECT hitbox;
	int ani_frame;
	int state, prev_state;
	int direction;
	int Pattern;
	float framedeleay;
	float Patterndeleay;
	
public:
	SBOSS(HINSTANCE, HWND);
	~SBOSS();
	void update(float);
	void animation(float);
	void draw(HDC, HWND);
	MY_PFLOAT getpos() const;
	POINT makepos(int, int);
	void update_hitbox();
	void move(float);
};