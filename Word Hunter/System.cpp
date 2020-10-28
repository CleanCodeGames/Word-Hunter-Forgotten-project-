#include "System.h"

sf::RenderWindow*		System::wnd;
sf::Clock				System::clock;
sf::Event				System::event;
sf::View				System::cam;
sf::Font*				System::font_modeka;
float					System::time;
float					System::time_in_pause;
int						System::scr_W;
int						System::scr_H;
float					System::scr_1;
float					System::scr_1w;
float					System::modifier_speed;
float					System::timer_Star2_sEff;
v2f						System::cam_p;
v2f						System::cur_p;
Texture*				System::texture;
enum System::GSTATE		System::gState;
enum System::LANGUAGE	System::language;
bool					System::isPauseGame;
bool					System::isShift;
bool					System::isSound_Music_On;
bool					System::isSound_Effects_On;
bool					System::isVideo_Smoth_On;
bool					System::isVideo_VertSync_On;
bool					System::isEffectStar;
uint					System::sound_Vol_Music;
uint					System::sound_Vol_Effects;

sf::FloatRect System::getVisible()
{
	return sf::FloatRect(float(cam_p.x - (scr_W/2)*1.4f), float(cam_p.y - (scr_H/2)*1.4f),  float(scr_W*1.8),  float(scr_H*1.8));
}

void System::SystemTime()
{
	time = float(clock.getElapsedTime().asMicroseconds() / 1000.f), clock.restart();
	if(!isPauseGame) time_in_pause = time;
	else time_in_pause = 0;
	if(isEffectStar) timer_Star2_sEff += time;
}

v2f System::NormalizePosition(v2f pos, float dist, float angle)
{
	dist*=scr_1;
	return pos + v2f(cosf(angle*PI/180.f)*dist,sinf(angle*PI/180.f)*dist);
}

void System::SystemCursor()
{
	if(event.type == sf::Event::MouseMoved)
		cur_p = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));
}


float System::getDist(v2f p1, v2f p2)
{
	return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

void System::ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, sf::Color col, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
	shp.setFillColor(col);
	shp.setTexture(&png);
}

void System::ConstructShapeW(Shape& shp, v2f pos, v2f siz, IMG& png, sf::Color col, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(v2f(pos.x*scr_1w, pos.y*scr_1));
	else shp.setPosition(pos);
	shp.setFillColor(col);
	shp.setTexture(&png);
}

void System::ConstructShape(Shape& shp, v2f pos, v2f siz, sf::Color col, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
	shp.setFillColor(col);
}

void System::ConstructText(sf::Text& text, v2f pos, float siz, sf::String str, sf::Font* font, sf::Color col)
{
	text.setFont(*font);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(uint(siz*scr_1));
	text.setColor(col);
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
	text.setPosition(pos);
}

uint System::getRandKeyNum()
{
	if (language == EN) return rand() % 26;
	else if (language == RU)
	{
		if (rand() % 32 < 25) return rand() % 26;
		else return (rand() % 6) + 46;
	}
}

System::System(void){}

System::System(void* init)
{
	if(init == "init")
	{
		isPauseGame = false;
		isShift = false;
		gState = main_menu;
		scr_W = GetSystemMetrics(0); 
		scr_H = GetSystemMetrics(1);
		scr_1 = scr_H / 100.f;
		scr_1w = scr_W / 100.f;
		time_in_pause = 0;
		time = 0;

		texture = new Texture;
		texture->setSmoth(true);
		font_modeka = new sf::Font;
		font_modeka->loadFromFile("Resources/Fonts/modeka.otf");

		wnd = new sf::RenderWindow(sf::VideoMode(scr_W,scr_H), "Game", sf::Style::Close, sf::ContextSettings(0,8,16));
		cam.reset(sf::FloatRect(0, 0, float(scr_W), float(scr_H)));
		cam.setCenter(0,0);
		cam_p = cam.getCenter();
		cur_p = v2f(0,0);
		wnd->setView(cam);
		wnd->setActive(false);

		srand(::time(0));
		clock.restart();
	}
}