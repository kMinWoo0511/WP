#pragma once
#include "stdafx.h"
#define BOSSSPEED 120
#define ATTACKSPEED 600
#define WARPTIME 2
#define DROPSPEED 550

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
	int HP;
	float randomPatternTime;
	float framedeleay;
	float Patterndeleay;
	float speed,attackspeed;
	float warpdeleay;
	bool warp;
	
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
	void update_state(float);
	int getaniframe() const;
	int getstate() const;
	int gethp() const;
	void sethp(int);
	void hitdamgetohp(int);
	RECT gethitbox() const;
	void collision();
};