#pragma once
#include "stdafx.h"

class EFFECT {
private:
	float x, y;
	float deleray;
	int frame;
	bool show;
	HBITMAP effect;
public:
	EFFECT(HBITMAP);
	~EFFECT();
	void seteffectpos(float, float);
	void update(float);
	void draw(HDC);
	bool getshow() const;
};