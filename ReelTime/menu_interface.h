#pragma once

#include <SFML/Graphics.hpp>

class MenuInterface : public sf::Sprite
{
public:
	MenuInterface();
private:
	sf::Texture* texture;
};