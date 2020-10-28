#pragma once
#include "oEffect_BG.h"

class oBackGround : public System
{
protected:

	Shape shape;
	vector<shared_ptr<oEffect_BG>> vec_Effect;
	float timer_effect_create;

public:
	 
	oBackGround() : timer_effect_create(0)
	{
	}

	virtual void Update()
	{
		timer_effect_create += time;
		for(auto& it = vec_Effect.begin(); it != vec_Effect.end();)
		{
			oEffect_BG& effect = *(*it);
			if(effect.isEnd()) it = vec_Effect.erase(it);
			else
			{
				effect.Update();
				it++;
			}
		}
	}

	virtual void Action()
	{

	}

	virtual void Draw()
	{
		wnd->draw(shape);
		for(auto effect: vec_Effect) effect->Draw();
	}

	virtual ~oBackGround() {}
};