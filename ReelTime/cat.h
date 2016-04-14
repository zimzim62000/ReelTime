#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "map_game.h"


class Cat : public Entity
{
public:
	Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, int speed);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
	bool Render(game_speed* gameSpeed, sf::RenderWindow* window);
	void MoveOnTarget(game_speed* gameSpeed);
	void AddTarget(const int x, const int y);
private:
	MapGame* mapGame;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	int countMove, countMoveMax;
	sf::CircleShape* targetView;
	sf::CircleShape* targetOneView;
};
