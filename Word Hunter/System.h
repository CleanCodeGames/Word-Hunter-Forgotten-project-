#pragma once
#include "Texture.h"
#include <Windows.h>
#define PI 3.1415

typedef unsigned int uint;
typedef sf::Vector2f v2f;
typedef sf::Vector2i v2i;
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;

class System
{
public:

	System(void* init);
	System(void);
	static void SystemTime();
	static void SystemCursor();
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, sf::Color col = sf::Color(255,255,255,255), const bool perc_pos = true);
	static void ConstructShapeW(Shape& shp, v2f pos, v2f siz, IMG& png, sf::Color col = sf::Color(255,255,255,255), const bool perc_pos = true);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, sf::Color col = sf::Color(255,255,255,255), const bool perc_pos = true);

	static void ConstructText(sf::Text& text, v2f pos, float siz, sf::String str, sf::Font* font, sf::Color col = sf::Color());

public:

	static sf::RenderWindow* wnd;
	static sf::Clock clock;
	static sf::Event event;
	static sf::View cam;
	static sf::Font *font_modeka;

	static float time;
	static float modifier_speed;
	static float time_in_pause;
	static int scr_W;
	static int scr_H;
	static float scr_1;
	static float scr_1w;
	static v2f cam_p;
	static v2f cur_p;
	static Texture* texture;
	static enum GSTATE {main_menu, game} gState;
	static enum LANGUAGE { EN, RU } language;
	static bool isPauseGame;
	static bool isShift;
	static float timer_Star2_sEff;
	static bool isEffectStar;

	static bool isSound_Music_On;
	static bool isSound_Effects_On;
	static bool isVideo_Smoth_On;
	static bool isVideo_VertSync_On;

	static uint sound_Vol_Music;
	static uint sound_Vol_Effects;

public:

	uint getRandKeyNum();
	static float getDist(v2f p1, v2f p2);
	static sf::FloatRect getVisible();
	static v2f NormalizePosition(v2f pos, float dist, float angle);

};

class LevelText : public System
{
public:

	sf::Text word;
	bool is_Use;

	LevelText(string str) : word(str, *font_modeka, uint(4*scr_1)), is_Use(false)
	{
		word.setStyle(sf::Text::Bold);
		const auto &rect = word.getGlobalBounds();
		word.setOrigin(rect.width/2, 0);
	}

	void Update()
	{

	}

	void Draw()
	{
		if(is_Use) wnd->draw(word);
	}

	~LevelText(void) { }
};

/*

#include <iostream> 
#include <windows.h> 

int main() 
{ 
WIN32_FIND_DATA win; 
char* buff = new char[255]; 
HANDLE han = FindFirstFile("G:\\dir\\*.doc*",&win); 
if(han != INVALID_HANDLE_VALUE) 
{ 
strcpy(buff,win.cFileName); 
strcat(buff," , "); 
while(FindNextFile(han,&win)) 
{ 
strcat(buff,win.cFileName); 
strcat(buff," , "); 
} 
std::cout « buff « std::endl; 
CloseHandle(han); 
} 


}

*/