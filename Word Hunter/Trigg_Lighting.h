#pragma once
#include "oTrigg.h"

class Trigg_Lighting : public oTrigg
{
private:

	Shape shpLighting;
	Shape shpFlash;
	float timer;

public:

	Trigg_Lighting(float unit_posX) : timer(1500)
	{
		ConstructShape(shpFlash, v2f(0,0), v2f(scr_W/scr_1,100), sf::Color(200,255,200,150), false);
		ConstructShape(shpLighting, v2f(unit_posX-(scr_1*3), -10), v2f(23,125), texture->Effect_Lighting_01, sf::Color(255,255,255,255), false);
	}

	virtual void Update()
	{
		if(!is_End && timer == 0) 
		{
			is_End = true;
		}
		else
		{
			timer -= time;
			if(timer <= 0) timer = 0;
			shpLighting.setFillColor(sf::Color(255,255,255,255*(timer/1500)));
			if(timer > 1250) shpFlash.setFillColor(sf::Color(200,255,200,150));
			else if(timer > 1000 && timer < 1250)
			{
				shpFlash.setFillColor(sf::Color(200,255,200,100));
			}
			else shpFlash.setFillColor(sf::Color(200,255,200,100*(timer/1000)));
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpFlash);
		wnd->draw(shpLighting);
	}

	virtual ~Trigg_Lighting() {}
};