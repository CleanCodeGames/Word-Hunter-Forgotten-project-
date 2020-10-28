#pragma once
#include "oTrigg.h"
#include "oUnit.h"

class Zzz : public System
{
private:

	float life_timer;
	static const int L_TIMER = 3200;
	Shape shape;
	float alpha;
	v2f p;

public:

	Zzz(v2f pos) : alpha(0)
	{
		life_timer = L_TIMER;
		ConstructShape(shape, pos, v2f(3,3), texture->Effect_Zzz, sf::Color(255, 255, 255, 255), false);
		p = shape.getPosition();
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual void Update()
	{
		life_timer -= time;
		alpha += time*0.0012;
		shape.setPosition(p.x + ((scr_1w * 2) * cosf( alpha )), p.y - ((scr_1 * 2) * sinf( alpha )));
		shape.setFillColor(sf::Color(255, 255, 255, 255 * ( life_timer / L_TIMER ) ));
	}

	virtual bool IsEnd() const
	{
		if(life_timer <= 0) return true;
		else return false;
	}

	virtual ~Zzz() {}
};

class Trigg_Sleep : public oTrigg
{
private:

	float duration;
	float pereodic;
	int count_z;
	vector<shared_ptr<Zzz>> vec_Z;
	vector<shared_ptr<oUnit>> *vec_Unit;

public:

	Trigg_Sleep(float duration, vector<shared_ptr<oUnit>> *vec_Unit) : pereodic(0), duration(duration), count_z(0)
	{
		this->vec_Unit = vec_Unit;
		for(auto unit: *this->vec_Unit) 
			unit->setState(unit->stand);
	}

	virtual void Update()
	{
		pereodic += time;
		duration -= time;

		if(pereodic >= 300 && count_z < 3)
		{
			count_z++;
			pereodic = 0;

			if(duration > 0)
			{
				for(auto unit: *vec_Unit)
					vec_Z.push_back(make_shared<Zzz>(Zzz(v2f(unit->shape.getPosition().x, unit->shape.getPosition().y - (unit->shape.getSize().y / 2.f) ))));
			}
		}
		else
		{
			if(pereodic >= 300)
			{
				if(count_z < 6) count_z++;
				else count_z = 0;
				pereodic = 0;
			}
		}
		for(auto& it = vec_Z.begin(); it != vec_Z.end();)
		{
			Zzz & z = *(*it);
			if(z.IsEnd())
			{
				it = vec_Z.erase(it);
			}
			else
			{
				if(!vec_Unit->empty())
				{
					for(auto unit: *vec_Unit)
					{
						if(unit->IsLife()) z.Update();
						else it = vec_Z.erase(it);
					}
				}
				it++;
			}
		}
	}

	virtual void Draw()
	{
		for(auto z: vec_Z) z->Draw();
	}

	virtual bool IsEnd() const
	{
		if(duration <= 0 && vec_Z.empty()) 
		{
			for(auto unit: *vec_Unit)
			{
				if(unit->IsLife())
				{
					unit->setState(unit->move);
				}
			}
			return true;
		}
		else return false;
	}

	virtual ~Trigg_Sleep() {}
};