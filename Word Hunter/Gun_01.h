#pragma once
#include "oGun.h"

class Gun_01 : public oGun
{
private:


public:

	Gun_01(v2f pos, v2f siz, IMG& img, v2f speed, LevelText& text, bool isMirror) 
		: oGun(pos, siz, img, speed, text, isMirror)
	{

	}


	virtual ~Gun_01(void) {}
};