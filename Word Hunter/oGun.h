#pragma once
#include "System.h"
#include "oUnit.h"

class oGun : public System
{
protected:

	
	v2f misssle_Speed;						// Скорость снарядов
	bool is_Mirror;							// Зеркальный

public:

	vector<shared_ptr<Shape>> vec_Missle;	// Снаряды
	string str_Needed;						// Нужная строка
	string str_Entered;						// Вводимая строка
	sf::Text text_Needed;					// Нужный текст
	sf::Text text_Entered;					// Вводимый текст
	static Shape shpFocus;
	Shape shape;

	oGun(v2f pos, v2f siz, IMG& img, v2f speed, LevelText& text, bool isMirror) :
		is_Mirror(isMirror),
		misssle_Speed(speed*scr_1),
		str_Entered(""),
		str_Needed(text.word.getString())
	{
		ConstructShape(shpFocus, pos, siz);
		shpFocus.setOutlineThickness(-scr_1/5.f);
		shpFocus.setOutlineColor(sf::Color::Green);
		shpFocus.setFillColor(sf::Color::Transparent);
		ConstructShape(shape, pos, siz, img);
		ConstructText(text_Needed, v2f(shape.getPosition().x, shape.getPosition().y - (scr_1 * siz.y)), 4, str_Needed, font_modeka, sf::Color(255,180,180,150));
		ConstructText(text_Entered, v2f(shape.getPosition().x, shape.getPosition().y - (scr_1 * siz.y)), 4, str_Entered, font_modeka, sf::Color(50,200,50));
		
		shpFocus.setPosition(shape.getPosition());
		if(isMirror) shape.setTextureRect(sf::IntRect(shape.getTexture()->getSize().x, 0, -shape.getTexture()->getSize().x, shape.getTexture()->getSize().y));
	}

	virtual void Update()
	{
		// Анимация
	}

	virtual void ResetWord(LevelText& text)
	{
		str_Needed = text.word.getString();
		text_Needed.setString(str_Needed);
	}

	virtual v2f getMissleSpeed()
	{
		return misssle_Speed*time;
	}

	virtual void Shoot()
	{
		vec_Missle.push_back(make_shared<Shape>(Shape()));
		const v2f &p = shape.getPosition();
		const v2f &s = shape.getSize();
		if(is_Mirror) ConstructShape(*vec_Missle.back(), v2f(p.x+s.x/2,p.y-s.y/4), v2f(6,3), texture->Effect_FireFly, sf::Color(255,255,255), false);
		else ConstructShape(*vec_Missle.back(), v2f(p.x-s.x/2,p.y-s.y/4), v2f(6,3), texture->Effect_FireFly, sf::Color(255,255,255), false);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(text_Needed);
		wnd->draw(text_Entered);
		for(auto missle: vec_Missle) wnd->draw(*missle);
	}

	virtual bool IsPicked() const
	{
		return shape.getGlobalBounds().intersects(shpFocus.getGlobalBounds());
	}

	virtual ~oGun()
	{

	}

	static void FocusSquareRotate();
	
};

void oGun::FocusSquareRotate()
{
	static float alpha = 0; 
	alpha+=time/1000.f;
	shpFocus.setOutlineColor(sf::Color(0, 255*fabs(cosf(alpha)), 255*fabs(sinf(alpha)), 100));
	shpFocus.setRotation(45*sin(alpha));
}

Shape oGun::shpFocus;