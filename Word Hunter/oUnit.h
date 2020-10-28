#pragma once
#include "Animation.h"

class oUnit : public System
{
protected:

	Shape indictor_hp;
	double hp, hp_max;
	v2f speed;
	float timer_corpse;

public:

	Shape shape;
	Animation anim_run;
	Animation anim_attack;
	Animation anim_death;
	Animation anim_stand; 
	enum STATE { stand, move, attack, death, corpse, destroy } state;

	oUnit(v2f pos, v2f siz, string name, v2f speed, uint hp, bool is_Mirror) 
		: 
		speed(speed*scr_1w),
		hp(hp), 
		hp_max(hp),
		state(move),
		timer_corpse(2000),
		anim_run(is_Mirror),
		anim_attack(is_Mirror),
		anim_death(is_Mirror),
		anim_stand(is_Mirror)
	{
		ConstructShape(indictor_hp, v2f(pos.x, pos.y-siz.y/1.5f), v2f(siz.x, 1.5f), sf::Color(50,255,50));
	}

	virtual void AnimResetAll()
	{
		anim_run.Reset();
		anim_attack.Reset();
		anim_death.Reset();
	}

	virtual void Update()
	{
		switch (state)
		{
			case oUnit::stand:{}break;
			case oUnit::move: shape.move(speed*time); break;
			case oUnit::attack: break;
			case oUnit::death: if(anim_death.End()) state = corpse; break;
			case oUnit::corpse:
				if((timer_corpse -= time) <= 0) state = destroy;
				else shape.setFillColor(sf::Color(255,255,255,255*(timer_corpse/2000)));
				break;
			case oUnit::destroy:
			{
				// Отправляем слово в окно с текстом
			}
			break;
		}

		if(state != corpse) indictor_hp.setPosition(v2f(shape.getPosition().x, shape.getPosition().y - (shape.getSize().y/1.5f)));
	}

	virtual void setState(STATE _state)
	{
		state = _state;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		if(state != corpse) wnd->draw(indictor_hp);
	}

	virtual void Damage(int dmg)
	{
		hp-=dmg;
		indictor_hp.setSize(v2f(shape.getSize().x * (hp/hp_max), 1.5*scr_1));
		if(hp <= 0)
		{
			indictor_hp.setSize(v2f(0,0));
			state = death;
			AnimResetAll();
		}
	}

	virtual bool IsLife()
	{
		if(state != death && state != corpse && state != destroy) return true;
		return false;
	}

	virtual ~oUnit()
	{

	}
};