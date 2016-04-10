#ifndef Field_Zim
#define Field_Zim

#pragma once

#include "entity.h"

class Field : public Entity
{
public:
	Field(EntityManager* entityManager, float x, float y, int speed);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
private:
	float speed, speedAngle, angle, engine, brakes, speedMax;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	sf::Vector2f direction;
	int count, countMax;
};

#endif Field_Zim