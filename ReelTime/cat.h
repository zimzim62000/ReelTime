#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "map_game.h"

class Cat : public Entity
{
public:
	Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, int speed);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
private:
	MapGame* mapGame;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	sf::Vector2f direction;
};
