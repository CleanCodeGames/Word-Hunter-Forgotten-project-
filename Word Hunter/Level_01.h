#pragma once
#include "Castle_01.h"
#include "BG_ForestMountain.h"
#include "oLevel.h"

class Level_01 : public oLevel
{
private:

	float timer_create;
	uint count;

public:
	
	Level_01(void) : timer_create(0)
	{
		ResetLevel();
		vec_BackGround.push_back(make_shared<BG_ForestMountain>(BG_ForestMountain()));
		vec_Castle.push_back(make_shared<Castle_01>(Castle_01(v2f(0,29), v2f(35,42), 10)));

		vec_Unit.push_back(make_shared<Unit_Golem_01>(Unit_Golem_01(v2f(50,42.5), v2f(15,15), "Golem", v2f(-0.0025, 0), 15, true)));
		vec_Unit.push_back(make_shared<Unit_Golem_01>(Unit_Golem_01(v2f(-50,42.5), v2f(15,15), "Golem", v2f(0.0025, 0), 15, false)));

		vec_Gun.push_back(make_shared<Gun_01>(Gun_01(v2f(-22, 45), v2f(12,12), //
			texture->Gun_01, v2f(-0.03, 0), *vec_Text[NextWord(vec_Text.size())], false)));
		vec_Gun.push_back(make_shared<Gun_01>(Gun_01(v2f( 22, 45), v2f(12,12), //
			texture->Gun_01, v2f( 0.03, 0), *vec_Text[NextWord(vec_Text.size())], true)));
	}

	inline void AddWord(string str)
	{
		vec_Text.push_back(make_shared<LevelText> (LevelText(str)));
	}

	virtual void ResetLevel()
	{
		vec_Text.clear();
		// I know how to make the rain pour, and shoot on the ogres.
		AddWord("I");
		AddWord("sleep");
		AddWord("sleep");
		AddWord("sleep");
		AddWord("know");
		AddWord("how");
		AddWord("to");
		AddWord("make");
		AddWord("the");
		AddWord("rain");
		AddWord("and");
		AddWord("lighting");
		AddWord("sleep");
		AddWord("sleep");
		AddWord("sleep");
		AddWord("and");
		AddWord("shoot");
		AddWord("on");
		AddWord("the");
		AddWord("ogres.");
		oLevel::ResetLevel();
	}
	
	virtual void Update()
	{
		oLevel::Update();
	}
	
	virtual void Draw()
	{
		oLevel::Draw();
	}

	virtual void Action()
	{
		oLevel::Action();
	}

	virtual ~Level_01(void)
	{

	}
};