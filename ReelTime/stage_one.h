#pragma once

#include "game_state.h"
#include "entity_manager.h"
#include "entity.h"
#include "game_speed.h"


class stage_one : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(float const dt, sf::RenderWindow* window);
	void Render(float const dt, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	game_speed* gameSpeed;

	EntityManager* manager;
	Entity* Test;
};