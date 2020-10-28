#pragma once
#include"oBackGround.h"
#include "Effect_FireFly.h"
class BG_ForestMountain : public oBackGround
{
public:

	BG_ForestMountain()
	{
		ConstructShape(shape, v2f(0,0), v2f(scr_W, scr_H)/scr_1, texture->ForestMountain[2]);
	}

	virtual void Update()
	{
		oBackGround::Update();
		if(timer_effect_create >= 100)
		{
			timer_effect_create = 0;
			vec_Effect.push_back(make_shared<Effect_FireFly>(Effect_FireFly(v2f(rand()%(int(scr_1*40)) - (scr_1*20), scr_H/2), v2f(10,10), texture->Effect_FireFly)));
		}
	}

	virtual void Action()
	{
		// ≈сли требуетс€ то обрабатываем тут ивенты
	}

	virtual void Draw()
	{
		oBackGround::Draw();
	}

	virtual ~BG_ForestMountain() {}
};