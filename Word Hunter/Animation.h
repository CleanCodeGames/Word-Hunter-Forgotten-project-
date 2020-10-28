#pragma once
#include "System.h"

class Animation : public System
{
public:
		uint MAX_FRAPS;
		uint FPS;
		uint curr;
		float timer;
		bool is_Mirror;

	Animation(bool is_Mirror) : curr(0), timer(0), is_Mirror(is_Mirror)
	{
		
	}

	virtual void setParam(const uint MAX_FRAPS, uint FPS) 
	{
		this->MAX_FRAPS = MAX_FRAPS;
		this->FPS = FPS;
	}

	virtual void Play(Shape& shape, IMG& img, bool isLoop = true)
	{
		if(FPS <= (timer += time))
		{
			curr++;
			timer = 0;
			if(curr >= MAX_FRAPS) 
			{
				if(isLoop) curr = 0;
				else curr = MAX_FRAPS;
			}
			shape.setTexture(&img);
			if(is_Mirror) shape.setTextureRect(sf::IntRect(img.getSize().x,0, -img.getSize().x,  img.getSize().y));
			else shape.setTextureRect(sf::IntRect(0,0, img.getSize().x,  img.getSize().y));
		}
	}

	virtual bool End()
	{
		if(curr == MAX_FRAPS) return true;
		else return false;
	}

	virtual void Reset() 
	{ 
		timer = 0; 
		curr = 0;
	}

	virtual ~Animation()
	{

	}
};