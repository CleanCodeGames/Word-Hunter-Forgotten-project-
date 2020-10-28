#pragma once
#include "oCastle.h"
#include "Gun_01.h"
class Castle_01 : public oCastle
{
public:
	
	Castle_01(v2f pos, v2f siz, uint hp) : oCastle(pos, siz, hp)
	{
		ConstructShape(shape, pos, siz, texture->Castle_01);
		
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
		oCastle::Draw();
	}
	
	virtual ~Castle_01(){}
};