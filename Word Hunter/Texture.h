#pragma once
#include<SFML\Graphics.hpp>
#include<sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>

typedef sf::Texture IMG;

using std::cout;
using std::endl;
using std::to_string;
using std::cos; 
using std::cosf;
using std::sin;
using std::sinf;
using std::atanf;
using std::make_shared;

typedef sf::Texture IMG;
using std::vector;
using std::string;
using std::shared_ptr;

class Texture
{
public:

	IMG ForestMountain[3];
	IMG Cyclop_Run[21], Cyclop_Attack[21], Cyclop_Dead[21], Cyclop_Stay[21];
	IMG Golem_01_Run[21], Golem_01_Attack[21], Golem_01_Dead[21], Golem_01_Stay[21];
	IMG Effect_FireFly;
	IMG Castle_01;
	IMG Gun_01;
	IMG Cloud_01;
	IMG Effect_Lighting_01;
	IMG Effect_Zzz;

private:

	inline void Load(IMG& texture, const string& file)
	{
		texture.loadFromFile("Resources/Textures/"+file);
	}

public: 

	void setSmoth(bool isSmoth)
	{
		for( int i = 0; i < 3; i++) ForestMountain[i].setSmooth(isSmoth);
		for(int i = 0; i < 62; i++) Cyclop_Run[i].setSmooth(isSmoth);
	}

	Texture()
	{
		Load ( Cloud_01, "Effects/Cloud.png");
		Load ( Effect_FireFly, "Effects/FireFly.png");
		Load ( Effect_Lighting_01, "Effects/Lighting.png");
		Load ( Effect_Zzz, "Effects/Zzz.png");

		Load ( Gun_01, "Gun/Gun_01.png");
		for( int i = 0; i < 3; i++) Load( ForestMountain[i], "BackGround/ForestMountain" + to_string(i+1) + ".png");
		Load (Castle_01, "Castle/Castle_01.png");

		for(int i = 0; i < 21; i++)
		{
			Load( Cyclop_Attack[i], "Unit/Cyclop/Attack/"+to_string(i)+".png");
			Load( Cyclop_Run[i], "Unit/Cyclop/Run/"+to_string(i)+".png");
			Load( Cyclop_Dead[i], "Unit/Cyclop/Death/"+to_string(i)+".png");
			Load( Cyclop_Stay[i], "Unit/Cyclop/Breath/"+to_string(i)+".png");

			Load( Golem_01_Attack[i], "Unit/Golem_01/Attack/"+to_string(i)+".png");
			Load( Golem_01_Run[i], "Unit/Golem_01/Run/"+to_string(i)+".png");
			Load( Golem_01_Dead[i], "Unit/Golem_01/Death/"+to_string(i)+".png");
			Load( Golem_01_Stay[i], "Unit/Golem_01/Breath/"+to_string(i)+".png");
		}
	}

	~Texture(void){}
};