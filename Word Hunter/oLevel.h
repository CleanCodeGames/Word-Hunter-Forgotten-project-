#pragma once
#include "oCastle.h"
#include "oBackGround.h"
#include "Unit_Cyclop.h"
#include "Unit_Golem_01.h"
#include "Gun_01.h"

#include "Trigg_Rain.h"
#include "Trigg_Lighting.h" 
#include "Trigg_Sleep.h"

class oLevel :
	public System
{
protected:

	int word_count;
	vector<shared_ptr<oCastle>> vec_Castle;
	vector<shared_ptr<oBackGround>> vec_BackGround;
	vector<shared_ptr<oUnit>> vec_Unit;
	vector<shared_ptr<oGun>> vec_Gun;
	vector<shared_ptr<LevelText>> vec_Text;
	vector<shared_ptr<oTrigg>> vec_Trigg;

public:
	
	oLevel(void) : word_count(0)
	{
	}

	virtual int NextWord(int vec_size)
	{
		if(vec_size > word_count) return word_count++;
		return vec_size-1;
	}
	
	virtual void Update()
	{
		oGun::FocusSquareRotate();

		for(auto back_ground: vec_BackGround) back_ground->Update();
		for(auto castle: vec_Castle) castle->Update();

		for(auto &it = vec_Unit.begin(); it != vec_Unit.end();)
		{
			oUnit& unit = *(*it);
			unit.Update();
			if(unit.state != unit.destroy) it++;
			else it = vec_Unit.erase(it);
		}

		for(auto & it = vec_Trigg.begin(); it != vec_Trigg.end();) 
		{
			oTrigg & trigg = *(*it);
			if(!trigg.IsEnd())
			{
				trigg.Update();
				it++;
			}
			else it = vec_Trigg.erase(it);
		}

		for(auto gun: vec_Gun) 
		{
			for(auto &it1 = vec_Unit.begin(); it1 != vec_Unit.end(); it1++)
			{
				oUnit& unit = *(*it1);
				if(unit.IsLife())
				{
					if(unit.shape.getGlobalBounds().intersects(gun->shape.getGlobalBounds()) && unit.state != unit.stand)
					{
						unit.setState(unit.STATE::attack);
					}

					for(auto it2 = gun->vec_Missle.begin(); it2 != gun->vec_Missle.end();)
					{
						Shape& missle = *(*it2);
						missle.move(gun->getMissleSpeed());
						if(missle.getGlobalBounds().intersects(unit.shape.getGlobalBounds()))
						{
							it2 = gun->vec_Missle.erase(it2);
							unit.Damage(1);
						}
						else
						{
							it2++;
						}
					}
				}
				if(unit.anim_attack.End()) 
				{
					// Нанести урон башне вышке
				}
			}
		}
	}
	
	virtual void Draw()
	{
		for(auto back_ground: vec_BackGround) back_ground->Draw();
		for(auto castle: vec_Castle) castle->Draw();
		for(auto unit: vec_Unit) unit->Draw();
		wnd->draw(oGun::shpFocus);
		for(auto gun: vec_Gun) gun->Draw();
		for(auto trigger: vec_Trigg) trigger->Draw();
		for(auto text: vec_Text) text->Draw();
	}

	virtual void Action()
	{
		for(auto back_ground: vec_BackGround) back_ground->Action();
		for(auto castle: vec_Castle) castle->Action();

		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == Key::Tab)
			{
				for(auto it = vec_Gun.begin(); it != vec_Gun.end();)
				{
					if((*it)->IsPicked()) 
					{
						if(it == vec_Gun.end()-1) oGun::shpFocus.setPosition(vec_Gun.front()->shape.getPosition());
						else 
						{
							it++;
							oGun::shpFocus.setPosition((*it)->shape.getPosition());
						}
						break;
					}
					it++;
				}
			}
		}
		
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == Key::LShift || event.key.code == Key::RShift) isShift = true;
			for(auto it: vec_Gun)
			{
				auto &gun = (*it);
				if(gun.IsPicked())
				{
					if(isShift)
					{
						if(event.key.code >= 0 && event.key.code < 26) // A-Z
							gun.str_Entered.push_back('A' + event.key.code);
						else
						{
							if(event.key.code == 26)					gun.str_Entered.push_back(')');
							else if(event.key.code == 27)				gun.str_Entered.push_back('!');
							else if(event.key.code == 28)				gun.str_Entered.push_back('@');
							else if(event.key.code == 29)				gun.str_Entered.push_back('#');
							else if(event.key.code == 30)				gun.str_Entered.push_back('$');
							else if(event.key.code == 31)				gun.str_Entered.push_back('%');
							else if(event.key.code == 32)				gun.str_Entered.push_back('^');
							else if(event.key.code == 33)				gun.str_Entered.push_back('&');
							else if(event.key.code == 34)				gun.str_Entered.push_back('*');
							else if(event.key.code == 35)				gun.str_Entered.push_back('(');
							else if(event.key.code == Key::LBracket)	gun.str_Entered.push_back('{');
							else if(event.key.code == Key::RBracket)	gun.str_Entered.push_back('}');
							else if(event.key.code == Key::SemiColon)	gun.str_Entered.push_back(':');
							else if(event.key.code == Key::Quote)		gun.str_Entered.push_back('\"');
							else if(event.key.code == Key::Space)		gun.str_Entered.push_back(' ');
							else if(event.key.code == Key::Comma)		gun.str_Entered.push_back('<');
							else if(event.key.code == Key::Period)		gun.str_Entered.push_back('>');
						}
					}
					else
					{
						if(event.key.code >= 0 && event.key.code < 26)			gun.str_Entered.push_back('a' + event.key.code);// a-z
						else if(event.key.code >= 26 && event.key.code < 36)	gun.str_Entered += to_string(event.key.code-26);// 0-9
						else if(event.key.code == Key::LBracket)				gun.str_Entered.push_back('[');
						else if(event.key.code == Key::RBracket)				gun.str_Entered.push_back(']');
						else if(event.key.code == Key::SemiColon)				gun.str_Entered.push_back(';');
						else if(event.key.code == Key::Quote)					gun.str_Entered.push_back('\'');
						else if(event.key.code == Key::Space)					gun.str_Entered.push_back(' ');
						else if(event.key.code == Key::Comma)					gun.str_Entered.push_back(',');
						else if(event.key.code == Key::Period)					gun.str_Entered.push_back('.');
					}
				}

				gun.text_Entered.setString(gun.str_Entered);
				for(int i = 0; i < gun.str_Entered.size(); i++)
				{
					if(gun.str_Needed[i] == gun.str_Entered[i])
					{ 
						if(i == gun.str_Needed.size()-1)
						{ 
							gun.str_Entered.clear();
							gun.text_Entered.setString(gun.str_Entered);
							for(auto text: vec_Text) 
							{
								if(!text->is_Use) 
								{
									if(text->word.getString() == gun.str_Needed)
									{
										if(!text->is_Use) // На слечай одинаковых слов в основном тексте
										{
											if(gun.str_Needed == "rain") vec_Trigg.push_back(make_shared<Trigg_Rain>(Trigg_Rain(18000)));

											if(gun.str_Needed == "lighting")
											{
												if(!vec_Unit.empty()) 
												{
													vec_Trigg.push_back(make_shared<Trigg_Lighting>(Trigg_Lighting(vec_Unit.back()->shape.getPosition().x)));
													vec_Unit.back()->Damage(10);
													if(!vec_Unit.back()->IsLife()) vec_Unit.back()->shape.setFillColor(sf::Color::Black);
												}
												else 
												{
													vec_Trigg.push_back(make_shared<Trigg_Lighting>(Trigg_Lighting(rand()%scr_W-(scr_W/2))));
												}
											}

											static float sleep_time = 5000;
											if(gun.str_Needed == "sleep") 
											{
												vec_Trigg.push_back(make_shared<Trigg_Sleep>(Trigg_Sleep(5000, &vec_Unit)));
											}
										}
										text->is_Use = true;
										break;
									}
								}
							}
							gun.Shoot();
							gun.ResetWord(*vec_Text[NextWord(vec_Text.size())]);
						} 
					} 
					else
					{
						gun.str_Entered.clear();
						gun.text_Entered.setString(gun.str_Entered);
					}
				}
			}
		}

		if(event.type == sf::Event::KeyReleased)
		{
			if(event.key.code == Key::LShift || event.key.code == Key::RShift) isShift = false;
		}
	}

	virtual void ResetLevel()
	{
		int line = 0;
		for(auto i = 0; i != vec_Text.size(); i++)
		{
			// Ссылки на текущий объект
			const auto & txt1 = vec_Text[i];
			const auto & str = txt1->word.getString().toAnsiString();
			const auto & rect1 = txt1->word.getGlobalBounds();
			const auto & wpos1 = txt1->word.getPosition();

			if(txt1 == vec_Text[0]) txt1->word.setPosition(v2f(-55 * scr_1 + rect1.width / 2, -45 * scr_1));
			else
			{
				// Ссылки на предыдущий объект
				const auto & txt2 = vec_Text[i-1];
				const auto & rect2 = txt2->word.getGlobalBounds();
				const auto & wpos2 = txt2->word.getPosition();

				v2f pos = v2f(wpos2.x + rect2.width / 2 + scr_1 + rect1.width / 2, wpos2.y);
				if(pos.x > scr_1 * 55)
				{
					line++;
					txt1->word.setPosition(v2f(-55 * scr_1 + rect1.width / 2, -45 * scr_1 + line * scr_1 * 5));
				}
				else txt1->word.setPosition(pos);
			}
		}
	}

	virtual ~oLevel(void)
	{

	}
};