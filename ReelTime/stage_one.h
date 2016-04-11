#pragma once

#include "game_state.h"
#include "entity_manager.h"
#include "entity.h"
#include "map_game.h"


class stage_one : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(game_speed* game_speed, sf::RenderWindow* window);
	void Render(game_speed* game_speed, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	EntityManager* manager;
	Entity* Test;
	MapGame* mapGame;
};