#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "map_game.h"


class Building : public Entity
{
public:
	Building(EntityManager* entityManager, MapGame* mapGame, float x, float y);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
	bool Render(game_speed* gameSpeed, sf::RenderWindow* window);
	//bool CheckCollision(Entity* entity);
	//bool CheckCollision();
	void Collision(Entity* entity);
	int getStock();
protected:
	MapGame* mapGame;
	EntityManager* entityManager;

	std::string name;
	int animationActive, nbAnimation, stock, stockMax;
	float timer, timerNextAnimated;

	std::vector<std::string> animation;
	
	sf::Font* font;
	sf::Text* stockText;
};