#pragma once
#include "stdafx.h"

EFFECT::EFFECT(HBITMAP _effect)
{
	effect = _effect;
	show = true;
	deleray = 0;
	frame = 0;
}

EFFECT::~EFFECT()
{
	printf("!23\n");
}

void EFFECT::update(float dt)
{
	deleray += dt;
	if (deleray >= 0.1f)
	{
		deleray = 0;
		frame++;
		if (frame >= 3) {
			show = false;
		}
	}
}

void EFFECT::draw(HDC memdc)
{
	HDC imagedc = CreateCompatibleDC(memdc);
	HBITMAP oldbit = (HBITMAP)SelectObject(imagedc, effect);
	//BitBlt(memdc, pos.x, pos.y, 400, 400, imagedc, 400 * frame, 600, SRCCOPY0
	float posx = x - 100;
	float posy = y - 75;
	TransparentBlt(memdc, posx, posy, 200, 150, imagedc, 400 * frame, 200, 400, 200, RGB(129, 130, 131));
	
	SelectObject(imagedc, oldbit);
	DeleteObject(imagedc);
}

void EFFECT::seteffectpos(float _x, float _y)
{
	x = _x;
	y = _y;
}

bool EFFECT::getshow() const
{
	return show;
}