#ifndef MainMenu_Zim
#define MainMenu_Zim

#pragma once

#include "game_state.h"

class intro_menu : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(game_speed* game_speed, sf::RenderWindow* window);
	void Render(game_speed* game_speed, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Font* font;
	sf::Text* title;
	sf::Text* play;
	sf::Text* quit;

	int selected;

	bool upKey, downKey;
};

#endif MainMenu_Zim