#pragma once
#include "Level_01.h"

class Game : public System
{
private:

	vector<shared_ptr<oLevel>> vec_Level;
	
public:

	Game() : System("init")
	{
		gState = game;
		vec_Level.push_back(make_shared<Level_01>(Level_01()));
		while (wnd->isOpen())
		{
			SystemTime();

			while(wnd->pollEvent(event))
			{
				SystemCursor();

				if(event.type == sf::Event::Closed) wnd->close();

				switch (gState)
				{
					case System::main_menu:

					break;

					case System::game:

						for(auto level: vec_Level) level->Action();

					break;
				}
			}

			switch (gState)
			{
				case System::main_menu:

				break;

				case System::game:

					for(auto level: vec_Level) level->Update();

				break;
			}
			
			wnd->clear();

			for(auto level: vec_Level) level->Draw();

			wnd->display();
		}
	}

	~Game() {}
};

