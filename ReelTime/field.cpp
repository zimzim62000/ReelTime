#include "stage_one.h"
#include "field.h"
#include <iostream>
#include "utility.h"


Field::Field(EntityManager* entityManager, float x, float y) : Entity()
{
	this->Load("fields2.png");
	this->setPosition(x, y);
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;

	this->count = 0;
	this->countMax = 10;
}

bool Field::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	if (gameSpeed->getGameTick() == true) {
		std::cout << "tick tick " << gameSpeed->getDeltaTime() << std::endl;
		this->count++;
		if (this->count > this->countMax) {
			this->count = 0;
			float tmp;
			tmp = utility::randInt(100, false);
			this->velocity.x = tmp / 50;
			tmp = utility::randInt(100, false);
			this->velocity.y = tmp / 50;
		}
	}

	if (this->getPosition().x < 0 || this->getPosition().x + this->getGlobalBounds().width > window->getSize().x) {
		this->velocity.x *= -1;
	}
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y) {
		this->velocity.y *= -1;
	}

	Entity::Update(gameSpeed, window);

	return true;
}