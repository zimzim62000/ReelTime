#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "map_game.h"
#include "building.h"


class Cat : public Entity
{
public:
	Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, int speed);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
	bool Render(game_speed* gameSpeed, sf::RenderWindow* window);
	void MoveOnTarget(game_speed* gameSpeed);
	void AddTarget(const int x, const int y);
	bool CheckCollision();
	bool CheckCollision(Entity* entity);
	void Collision(Entity* entity);

private:
	void collisionBuilding(Entity* entity);

	MapGame* mapGame;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	int countMove, countMoveMax, stock;
	sf::CircleShape* targetView;
	sf::CircleShape* targetOneView;

	sf::Font* font;
	sf::Text* stockText;

	std::vector<sf::Vertex> pathLine;
};
