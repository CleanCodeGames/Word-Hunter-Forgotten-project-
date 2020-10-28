#pragma once
#include "System.h"

class oCastle : public System
{
protected:

	uint hp;
	Shape shape;

public:
	
	oCastle(v2f pos, v2f siz, uint hp) : hp(hp)
	{
	}

	virtual void Damage(uint& dmg)
	{
		hp -= dmg;
	}

	virtual void Update()
	{

	}

	virtual void Action()
	{

	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~oCastle(){}
};