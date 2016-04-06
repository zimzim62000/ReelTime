#include "stage_one.h"
#include "field.h"
#include <iostream>
#include "utility.h"


Field::Field(EntityManager* entityManager, float x, float y) : Entity()
{
	this->Load("field.png");
	this->setPosition(x, y);
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;
}

bool Field::Update(float const dt, sf::RenderWindow* window)
{

	Entity::Update(dt, window);

	return true;
}