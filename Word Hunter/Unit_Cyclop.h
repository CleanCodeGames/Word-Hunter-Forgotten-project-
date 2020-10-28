#pragma once
#include "oUnit.h"

class Unit_Cyclop : public oUnit
{
public:

	Unit_Cyclop(v2f pos, v2f siz, string name, v2f speed, uint hp, bool is_Mirror) : 
		oUnit(pos, siz, name, speed, hp, is_Mirror)
	{
		ConstructShapeW(shape, pos, siz, texture->Cyclop_Run[0]);
		anim_run.setParam(21,60);
		anim_attack.setParam(21,60);
		anim_death.setParam(21,60);
		anim_stand.setParam(21,60); 
	}

	virtual void Update()
	{
		switch (state)
		{
			case oUnit::stand: anim_stand.Play(shape,texture->Cyclop_Stay[anim_stand.curr]); break;
			case oUnit::move: anim_run.Play(shape, texture->Cyclop_Run[anim_run.curr]); break;
			case oUnit::attack: anim_attack.Play(shape, texture->Cyclop_Attack[anim_attack.curr]); break;
			case oUnit::death: anim_death.Play(shape, texture->Cyclop_Dead[anim_death.curr], false); break;
		}
		oUnit::Update();
	}

	virtual void Draw()
	{
		oUnit::Draw();
	}

	virtual void Damage(int dmg)
	{
		oUnit::Damage(dmg);
	}


	virtual ~Unit_Cyclop()
	{

	}
};