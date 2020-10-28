#pragma once
#include "oTrigg.h"

class Rain : public System
{
public:

	Shape shape;
	v2f speed;

	Rain(v2f pos)
	{
		speed = v2f(-0.003*scr_1w,0.01*scr_1)*float(rand()%6+3);
		ConstructShape(shape, pos, v2f(0.25, float(rand()%20+5)/10.f), sf::Color(100,100,255,rand()%40+50), false);
		shape.setRotation(20);
	}
	virtual ~Rain(){}
};

class Trigg_Rain : public oTrigg
{
private:
	
	Shape cloud;
	vector<shared_ptr<Rain>> vec_Rain;
	float timer;
	float duration;

public:

	Trigg_Rain(float duration) 
		: timer(0), duration(duration) 
	{
		ConstructShape(cloud,v2f(-20,-32.5), v2f(scr_W/scr_1, 25)*1.75f, texture->Cloud_01, sf::Color(255,255,255,0), true);
	}

	virtual void Update()
	{
		timer += time;
		duration -= time;
		cloud.move(0.002*time*scr_1w,0);
		if(timer > 0.5) 
		{
			if(duration > 0) 
			{
				if(cloud.getFillColor().a < 255) cloud.setFillColor(sf::Color(255,255,255,cloud.getFillColor().a+1));
				timer = 0;
				vec_Rain.push_back(make_shared<Rain>(Rain(v2f(cloud.getPosition().x+rand()%int(cloud.getSize().x)-(cloud.getSize().x/2),cloud.getPosition().y))));
			}
			else if(cloud.getFillColor().a > 1) cloud.setFillColor(sf::Color(255,255,255,cloud.getFillColor().a-1));
		}

		for(auto &it = vec_Rain.begin(); it != vec_Rain.end();)
		{
			Rain & rain = *(*it);

			if(rain.shape.getPosition().y < scr_H/2)
			{
				rain.shape.move(rain.speed*time);
				it++;
			}
			else it = vec_Rain.erase(it);
		}

		if(duration <= 0 && vec_Rain.empty()) 
			is_End = true;
	}

	virtual void Draw()
	{
		for(auto rain: vec_Rain) 
			wnd->draw(rain->shape); 
		wnd->draw(cloud);
	}

	virtual ~Trigg_Rain() { }
};