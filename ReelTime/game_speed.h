#pragma once

#include <SFML/Graphics.hpp>

class game_speed : public sf::Sprite
{
public:
	game_speed();
	void Initialize(sf::RenderWindow* window);
	bool Update(float const dt, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
	bool Paused();
	bool getGameTick();
	int getGameSpeed();
	float getDeltaTime();
	float getGameSpeedDeltaTime();
private:
	void generateSprite();

	sf::Font* font;
	sf::Text* counter;
	sf::Text* speedText;
	sf::Text* pauseText;

	sf::Texture* texture;
	sf::Image* tileSetTexture, ImgPauseActive, ImgPauseInactive, ImgPlayActive, ImgPlayInactive;

	float deltaTime, deltaTimeCounter, deltaTimeSecond;
	int gameSpeed, gameSpeedMax, gameSpeedMin, tileWidth, tileHeight;
	bool gamePause, subtractKey, addKey, echapKey, gameTick;
};