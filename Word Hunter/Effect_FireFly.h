#pragma once
#include "oEffect_BG.h"

class Effect_FireFly : public oEffect_BG
{
private:

	float life_timer;
	float alpha;
	float px;
	static const int L_TIMER = 4000;

public:

	Effect_FireFly(v2f pos, v2f siz, IMG& img) : oEffect_BG()
	{
		alpha = 0;
		life_timer = L_TIMER;
		ConstructShape(shape, pos, siz, img, sf::Color(255,255,255), false);
		px = shape.getPosition().x;
	}

	virtual void Update()
	{
		life_timer -= time;
		alpha += time/75;
		shape.move(v2f(0, -0.03f)*(scr_1*time));
		shape.setPosition(px+(scr_1*cosf(alpha)*3), shape.getPosition().y);
		shape.setFillColor(sf::Color(255,255,255, 255*(life_timer/L_TIMER)));
	}

	virtual bool isEnd() const
	{
		return life_timer > 0 ? false : true;
	}

	virtual void Draw()
	{
		oEffect_BG::Draw();
	}

	virtual ~Effect_FireFly(){}
};