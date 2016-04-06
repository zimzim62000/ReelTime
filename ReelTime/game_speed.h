#pragma once

#include <SFML/Graphics.hpp>

class game_speed : public sf::Sprite
{
public:
	game_speed();
	void Initialize(sf::RenderWindow* window);
	bool Update(float const dt, sf::RenderWindow* window);
	void Render(float const dt, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
	bool Paused();
	int getGameSpeed();
private:
	void generateSprite();

	sf::Font* font;
	sf::Text* counter;
	sf::Text* speedText;
	sf::Text* pauseText;

	sf::Texture* texture;
	sf::Image* tileSetTexture, ImgPauseActive, ImgPauseInactive, ImgPlayActive, ImgPlayInactive;

	int gameSpeed, gameSpeedMax, gameSpeedMin, tileWidth, tileHeight;
	bool gamePause, subtractKey, addKey, echapKey;
};